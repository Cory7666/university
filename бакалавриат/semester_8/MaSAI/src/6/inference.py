# inference.py
# ------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


import itertools
import random
import busters
import game
import util
from util import manhattanDistance, raiseNotDefined


class DiscreteDistribution(dict):

    def __getitem__(self, key):
        self.setdefault(key, 0)
        return dict.__getitem__(self, key)

    def copy(self):
        
        return DiscreteDistribution(dict.copy(self))

    def argMax(self):
        
        if len(self.keys()) == 0:
            return None
        all = list(self.items())
        values = [x[1] for x in all]
        maxIndex = values.index(max(values))
        return all[maxIndex][0]

    def total(self):
        
        return float(sum(self.values()))

    def normalize(self):
        
        total = float(self.total())
        if total !=0:
             for key in self.keys():
                 self[key]=self[key]/ total
       

    def sample(self):
        
        items = sorted (self.items())
        
        distribution = [i[1] for i in  items]
                 
        item_values = [i[0] for  i in  items]
        random_choice =random.random()
                 
        i,total =0,distribution[0]
                 
        if self.total()!=1:
            self.normalize()
                 
        while random_choice > total:
            i +=1
            total +=distribution[i]
        
        return item_values[i]
        


class InferenceModule:
   

    def __init__(self, ghostAgent):
        
        self.ghostAgent = ghostAgent
        self.index = ghostAgent.index
        self.obs = []  # most recent observation position

    def getJailPosition(self):
        return (2 * self.ghostAgent.index - 1, 1)

    def getPositionDistributionHelper(self, gameState, pos, index, agent):
        try:
            jail = self.getJailPosition()
            gameState = self.setGhostPosition(gameState, pos, index + 1)
        except TypeError:
            jail = self.getJailPosition(index)
            gameState = self.setGhostPositions(gameState, pos)
        pacmanPosition = gameState.getPacmanPosition()
        ghostPosition = gameState.getGhostPosition(index + 1)  # The position you set
        dist = DiscreteDistribution()
        if pacmanPosition == ghostPosition:  # The ghost has been caught!
            dist[jail] = 1.0
            return dist
        pacmanSuccessorStates = game.Actions.getLegalNeighbors(pacmanPosition, \
                gameState.getWalls())  # Positions Pacman can move to
        if ghostPosition in pacmanSuccessorStates:  # Ghost could get caught
            mult = 1.0 / float(len(pacmanSuccessorStates))
            dist[jail] = mult
        else:
            mult = 0.0
        actionDist = agent.getDistribution(gameState)
        for action, prob in actionDist.items():
            successorPosition = game.Actions.getSuccessor(ghostPosition, action)
            if successorPosition in pacmanSuccessorStates:  # Ghost could get caught
                denom = float(len(actionDist))
                dist[jail] += prob * (1.0 / denom) * (1.0 - mult)
                dist[successorPosition] = prob * ((denom - 1.0) / denom) * (1.0 - mult)
            else:
                dist[successorPosition] = prob * (1.0 - mult)
        return dist

    def getPositionDistribution(self, gameState, pos, index=None, agent=None):
        
        if index == None:
            index = self.index - 1
        if agent == None:
            agent = self.ghostAgent
        return self.getPositionDistributionHelper(gameState, pos, index, agent)

    def getObservationProb(self, noisyDistance, pacmanPosition, ghostPosition, jailPosition):
        
        
        if ghostPosition == jailPosition:
                         # 。 If the noise distance between Pacman and the ghost is None, the probability of a noise distance being None is 1
            if noisyDistance == None:
                return 1.0
                         # , Pacman and ghost noise distance is not None, the probability is 0
            else:
                return 0.0
 
                 #If the ghost is not in the ghost jail, the probability that the noise distance between Pacman and the ghost is None is 0.
        if noisyDistance == None :
            return 0.0
                 #If the noise distance between Pacman and the ghost is not None, obtain the probabilityDistributions[noisyDistance][trueDistance] probability distribution value according to the noise distance and the actual distance.
        return busters.getObservationProbability(noisyDistance, manhattanDistance(pacmanPosition, ghostPosition))
        


    def setGhostPosition(self, gameState, ghostPosition, index):
        
        conf = game.Configuration(ghostPosition, game.Directions.STOP)
        gameState.data.agentStates[index] = game.AgentState(conf, False)
        return gameState

    def setGhostPositions(self, gameState, ghostPositions):
       
        for index, pos in enumerate(ghostPositions):
            conf = game.Configuration(pos, game.Directions.STOP)
            gameState.data.agentStates[index + 1] = game.AgentState(conf, False)
        return gameState

    def observe(self, gameState):
        
        distances = gameState.getNoisyGhostDistances()
        if len(distances) >= self.index:  # Check for missing observations
            obs = distances[self.index - 1]
            self.obs = obs
            self.observeUpdate(obs, gameState)

    def initialize(self, gameState):
       
        self.legalPositions = [p for p in gameState.getWalls().asList(False) if p[1] > 1]
        self.allPositions = self.legalPositions + [self.getJailPosition()]
        self.initializeUniformly(gameState)


    def initializeUniformly(self, gameState):
       
        raise NotImplementedError

    def observeUpdate(self, observation, gameState):
        
        raise NotImplementedError

    def elapseTime(self, gameState):
       
        raise NotImplementedError

    def getBeliefDistribution(self):
       
        raise NotImplementedError


class ExactInference(InferenceModule):
   
    def initializeUniformly(self, gameState):
        
        self.beliefs = DiscreteDistribution()
        for p in self.legalPositions:
            self.beliefs[p] = 1.0
        self.beliefs.normalize()

    def observeUpdate(self, observation, gameState):
        pacmanPosition=gameState.getPacmanPosition()
        jailPosition=self.getJailPosition()
        positions=self.allPositions
        noisyDistance=observation
        for possibleGhostPos in positions:
            self.beliefs[possibleGhostPos] = self.getObservationProb(noisyDistance, pacmanPosition, possibleGhostPos, jailPosition)*self.beliefs[possibleGhostPos]
            self.beliefs.normalize()
        self.beliefs.normalize()

           

    def elapseTime(self, gameState):
       
        # определяем возможные позции призрака
        positions=self.allPositions
         # создаем экземпляр распределения
        beliefDict=DiscreteDistribution()
         
         # выполняем итерации по всем возможным позициям призрака
        for ghostPos in positions:
         # определяем распределение новых позиций призрака
         # по предыдущей позиции ghostPos
            newPosDist = self.getPositionDistribution(gameState, ghostPos)
         # для всех элементов распределения newPosDist
            for newPos, prob in newPosDist.items():
         # обновляем степени доверия возможных новых позиций
                beliefDict[newPos]=beliefDict[newPos]+self.beliefs[ghostPos]*prob
         # нормализуем распределение 
        beliefDict.normalize
         # сохраняем обновленное распределение
        self.beliefs=beliefDict        
        

    def getBeliefDistribution(self):
        return self.beliefs


class ParticleFilter(InferenceModule):
   
    def __init__(self, ghostAgent, numParticles=300):
        InferenceModule.__init__(self, ghostAgent)
        self.setNumParticles(numParticles)

    def setNumParticles(self, numParticles):
        self.numParticles = numParticles

    def initializeUniformly(self, gameState):
       
        self.particles = []
       
        num = 0
        while num < self.numParticles:
            for p in self.legalPositions:
                if num >= self.numParticles: break
                self.particles.append(p)
                num += 1
                
    def observeUpdate(self, observation, gameState):
        
        weights=DiscreteDistribution()
        resample=[]
        # определяем позиции Пакмана и тюрьмы

        pacmanPosition=gameState.getPacmanPosition()
        jailPosition=self.getJailPosition()
        # для каждой позиции частицы
        for pos in self.particles:
        # определяем степень уверенности наблюдения при заданных
        # pacmanPosition, pos, jailPosition и аккумулируем в виде веса
            weights[pos]+=self.getObservationProb(observation, pacmanPosition, pos, jailPosition)
            # если частицы получают нулевой вес
        if weights.total()==0:
        # то инициализаируем повторно список частиц
            self.initializeUniformly(gameState)
        # иначе
        else:
            # нормазизуем распределение весов
            weights.normalize()
            # формируем список частиц путем выборки из распределния весов
            self.particles = [weights.sample() for _ in range(int(self.numParticles))]
        #raiseNotDefined()
        
    def elapseTime(self, gameState):
        
        elapseDist=DiscreteDistribution()
 # определяем выборку в виде списка позиций частиц
        sample=self.particles
 # для каждой позиции частицы
        for pos in sample:
 # находим распределение в следующей возможной позиции
            newPosDist = self.getPositionDistribution(gameState, pos)
 # для всех элементов распределения newPosDist
            for newPos, prob in newPosDist.items():
 # обновляем степени доверия возможных новых позиций
                elapseDist[newPos]+=prob
 # нормализуем распределение
        elapseDist.normalize()
 # формируем новый список частиц путем выборки из распределния 
        self.particles=[elapseDist.sample() for _ in range(int(self.numParticles))]
 #raiseNotDefined()

        
    def getBeliefDistribution(self):
        
        answer = util.Counter()
        for particle in self.particles:
            answer[particle] += 1
        answer.normalize()
        return answer
        #raiseNotDefined()


class JointParticleFilter(ParticleFilter):
    
    def __init__(self, numParticles=600):
        self.setNumParticles(numParticles)

    def initialize(self, gameState, legalPositions):
        
        self.numGhosts = gameState.getNumAgents() - 1
        self.ghostAgents = []
        self.legalPositions = legalPositions
        self.initializeUniformly(gameState)

    def initializeUniformly(self, gameState):
        
        #self.particles = []
        self.particles = []
        permutations = list(itertools.product(self.legalPositions, repeat=self.numGhosts))
        random.shuffle(permutations)
        size = self.numParticles
        i = 0
        while i < size:
            for particle in permutations:
                self.particles.append(particle)
                i += 1
        
    def addGhostAgent(self, agent):
       
        self.ghostAgents.append(agent)

    def getJailPosition(self, i):
        return (2 * i + 1, 1)

    def observe(self, gameState):
        
        observation = gameState.getNoisyGhostDistances()
        self.observeUpdate(observation, gameState)

    def observeUpdate(self, observation, gameState):
        
        pacmanPosition = gameState.getPacmanPosition()
        newPD = DiscreteDistribution()
        
        for ghostPositions in self.particles:
            
            prob = 1
            for i in range(self.numGhosts):
                prob *= self.getObservationProb(observation[i], pacmanPosition, ghostPositions[i],self.getJailPosition(i))
            newPD[ghostPositions] += prob
        
        if newPD.total() == 0:
            self.initializeUniformly(gameState)
        else:
           
            newPD.normalize()
           
            self.particles = [newPD.sample() for _ in range(self.numParticles)]
       
        #raiseNotDefined()

    def elapseTime(self, gameState):
        
        
        """
        Sample each particle's next state based on its current state and the
        gameState.
        """
        newParticles = []
        for oldParticle in self.particles:
            newParticle = list(oldParticle)  # A list of ghost positions

            # now loop through and update each entry in newParticle...
            "*** YOUR CODE HERE ***"
            
            for i in range(self.numGhosts):
                newPosDist = self.getPositionDistribution(gameState, newParticle, i, self.ghostAgents[i])
                newParticle[i] = newPosDist.sample()
            """*** END YOUR CODE HERE ***"""
            newParticles.append(tuple(newParticle))
        self.particles = newParticles


jointInference = JointParticleFilter()


class MarginalInference(InferenceModule):
    
    def initializeUniformly(self, gameState):
       
        if self.index == 1:
            jointInference.initialize(gameState, self.legalPositions)
        jointInference.addGhostAgent(self.ghostAgent)

    def observe(self, gameState):
        
        if self.index == 1:
            jointInference.observe(gameState)

    def elapseTime(self, gameState):
        
        if self.index == 1:
            jointInference.elapseTime(gameState)

    def getBeliefDistribution(self):
      
        jointDistribution = jointInference.getBeliefDistribution()
        dist = DiscreteDistribution()
        for t, prob in jointDistribution.items():
            dist[t[self.index - 1]] += prob
        return dist
