# valueIterationAgents.py
# -----------------------
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


# valueIterationAgents.py
# -----------------------
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


import mdp, util

from learningAgents import ValueEstimationAgent
import collections

class ValueIterationAgent(ValueEstimationAgent):
    """
        * Пожалуйста, прочтите learningAgents.py перед тем, как читать это. *

         ValueIterationAgent принимает марковский процесс принятия решений
         (см. mdp.py) при инициализации и выполняет итерацию по значениям
         для заданного количества итераций с использованием 
         коэффициента дисконтирования.
        
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100):
        """
          Ваш агент итераций по значениям должен принимать mdp при
          вызове конструктора, запустите его с указанным количеством итераций,
          а затем действуйте в соответствии с полученной политикой.

           Некоторые полезные методы mdp, которые вы будете использовать:
              mdp.getStates() - возвращает список состояний MDP
              mdp.getPossibleActions(state) - возвращает кортеж возможных действий в состоянии
              mdp.getTransitionStatesAndProbs(state, action)- возвращает список из пар (nextState, prob) - s' и вероятности переходов T(s,a,s')
              mdp.getReward(state, action, nextState) - вовращает награду R(s,a,s')
              mdp.isTerminal(state)- проверяет, является ли состояние терминальным
        """
        self.mdp = mdp
        self.discount = discount
        self.iterations = iterations
        self.values = util.Counter() # Counter - словарь ценностей состояний, по умолчанию содержит 0
        self.runValueIteration()

    def runValueIteration(self):
        # Напишите код, реализующий итерации по значениям 
        "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
        for i in range(self.iterations):
          states = self.mdp.getStates()
          temp_counter = util.Counter()
          for state in states:
            max_val = float("-inf")
            for action in self.mdp.getPossibleActions(state):
              q_value = self.computeQValueFromValues(state, action)
              if q_value > max_val:
                max_val = q_value
              temp_counter[state] = max_val
          self.values = temp_counter       

    def getValue(self, state):
        """
          Возвращает ценность состояния (вычисляется в  __init__).
        """
        return self.values[state]


    def computeQValueFromValues(self, state, action):
        """
          Вычисляет Q-ценность в состоянии по
          значению ценности состояния, сохраненному в self.values.
        """
        action_prob_pairs = self.mdp.getTransitionStatesAndProbs(state, action)
        total = 0
        for next_state, prob in action_prob_pairs:
            reward = self.mdp.getReward(state, action, next_state)
            total += prob * (reward + self.discount * self.values[next_state])
        return total       
        util.raiseNotDefined()

    def computeActionFromValues(self, state):
        """
          Определяет политику - лучшее действие в  состоянии
          в соответствии с ценностями, хранящимися в  self.values.

          Обратите внимание, что если нет никаких допустимых действий,
          как в случае  терминального состояния, необходимо вернуть None.
        """
        "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
        best_action = None
        max_val = float("-inf")
        for action in self.mdp.getPossibleActions(state):
          q_value = self.computeQValueFromValues(state, action)
          if q_value > max_val:
            max_val = q_value
            best_action = action
        return best_action

    def getPolicy(self, state):
        return self.computeActionFromValues(state)

    def getAction(self, state):
        "Возвращает политику в состоянии (без исследования)"
        return self.computeActionFromValues(state)

    def getQValue(self, state, action):
        return self.computeQValueFromValues(state, action)

class AsynchronousValueIterationAgent(ValueIterationAgent):
    """
         * Пожалуйста, прочтите learningAgents.py перед тем, как читать это. *

         AsynchronousValueIterationAgent принимает марковский процесс принятия решений
         (см. mdp.py) при инициализации и выполняет итерацию по значениям
         для заданного количества итераций с использованием 
         коэффициента дисконтирования.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 1000):
        """
          Ваш агент итераций по значениям должен принимать mdp при
          вызове конструктора, запустите его с указанным количеством итераций,
          а затем действуйте в соответствии с полученной политикой.
          Каждая итерация обновляет значение только одного состояния,
          которое циклически выбирается из списка состояний. 
          Если выбранное состояние является конечным, на этой итерации ничего
          не происходит.


          Некоторые полезные методы mdp, которые вы будете использовать:    
              mdp.getStates() - возвращает список состояний MDP
              mdp.getPossibleActions(state) - возвращает кортеж возможных действий в состоянии
              mdp.getTransitionStatesAndProbs(state, action)- возвращает список из пар (nextState, prob) - s' и вероятности переходов T(s,a,s')
              mdp.getReward(state, action, nextState) - вовращает награду R(s,a,s')
              mdp.isTerminal(state)- проверяет, является ли состояние терминальным
        """
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    def runValueIteration(self):
        # Напишите код, реализующий асинхронные итерации по значениям 
        "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
        states = self.mdp.getStates()
        num_states = len(states)
        for i in range(self.iterations):
          state = states[i % num_states]
          if not self.mdp.isTerminal(state):
            values = []
            for action in self.mdp.getPossibleActions(state):
              q_value = self.computeQValueFromValues(state, action)
              values.append(q_value)
            self.values[state] = max(values)       
        

class PrioritizedSweepingValueIterationAgent(AsynchronousValueIterationAgent):
    """
        * Пожалуйста, прочтите learningAgents.py перед тем, как читать это. *

        Агент PrioritizedSweepingValueIterationAgent принимает марковский
        процесс принятия решения (см. Mdp.py) при инициализации и выполняет 
        итерации по значениям  с разверткой приоритетных состояний при 
        заданном числе  итераций с использованием предоставленных параметров.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100, theta = 1e-5):
        """
          Ваш агент итерации по развертке приоритетных значений должен 
          принимать на вход МДП при создании, выполнять заданое количество итераций, 
          а затем действовать в соответствии с полученной политикой.
        """
        self.theta = theta
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    def runValueIteration(self):
        
        "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
        pq = util.PriorityQueue()
        predecessors = {}
        for state in self.mdp.getStates():
          if not self.mdp.isTerminal(state):
            for action in self.mdp.getPossibleActions(state):
              for nextState, prob in self.mdp.getTransitionStatesAndProbs(state, action):
                if nextState in predecessors:
                  predecessors[nextState].add(state)
                else:
                  predecessors[nextState] = {state}

        for state in self.mdp.getStates():
          if not self.mdp.isTerminal(state):
            values = []
            for action in self.mdp.getPossibleActions(state):
              q_value = self.computeQValueFromValues(state, action)
              values.append(q_value)
            diff = abs(max(values) - self.values[state])
            pq.update(state, - diff)

        for i in range(self.iterations):
          if pq.isEmpty():
            break
          temp_state = pq.pop()
          if not self.mdp.isTerminal(temp_state):
            values = []
            for action in self.mdp.getPossibleActions(temp_state):
              q_value = self.computeQValueFromValues(temp_state, action)
              values.append(q_value)
            self.values[temp_state] = max(values)

          for p in predecessors[temp_state]:
            if not self.mdp.isTerminal(p):
              values = []
              for action in self.mdp.getPossibleActions(p):
                q_value = self.computeQValueFromValues(p, action)
                values.append(q_value)
              diff = abs(max(values) - self.values[p])
              if diff > self.theta:
                pq.update(p, -diff)       
        

