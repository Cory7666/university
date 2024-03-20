# searchAgents.py
# ---------------
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


"""
Этот файл содержит всех агентов, которые могут быть выбраны для управления Pacman.
Чтобы выбрать агента, используйте опцию «-p» при запуске pacman.py. Аргументы
могут быть переданы вашему агенту с помощью '-a'. Например, чтобы загрузить
SearchAgent, который использует поиск в глубину (dfs), выполните следующую
команду:

> python pacman.py -p SearchAgent -a fn=depthFirstSearch

Команды для вызова других стратегий поиска можно найти в описании заданий.

Пожалуйста, измените только те части файла, которые необходимо. Для этого
найдите строку-приглашение 

"*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"

и вставьте код после этой строки (саму строку-приглашение не удаляйте)

"""

from game import Directions
from game import Agent
from game import Actions
import util
import time
import search

class GoWestAgent(Agent):
    "An agent that goes West until it can't."

    def getAction(self, state):
        "The agent receives a GameState (defined in pacman.py)."
        if Directions.WEST in state.getLegalPacmanActions():
            return Directions.WEST
        else:
            return Directions.STOP

#######################################################
# Эта часть уже написана, но будет работать только    #
#       после того, как вы заполните search.py        #
#######################################################

class SearchAgent(Agent):
    """
   Это общий поисковый агент, находящий путь с помощью предоставленного 
   алгоритма поиска для поставленной задачи поиска. Возвращает действия,
   обеспечивающие прохождение пути.

   По умолчанию этот агент запускает DFS для PositionSearchProblem, чтобы 
   найти местоположение с координатами (1,1)

   Параметры для fn включают:
       depthFirstSearch или dfs
       widththFirstSearch или bfs

   Примечание. Вам НЕ следует изменять какой-либо код в SearchAgent.
    """

    def __init__(self, fn='depthFirstSearch', prob='PositionSearchProblem', heuristic='nullHeuristic'):
        # Warning: some advanced Python magic is employed below to find the right functions and problems

        # Get the search function from the name and heuristic
        if fn not in dir(search):
            raise AttributeError(fn + ' is not a search function in search.py.')
        func = getattr(search, fn)
        if 'heuristic' not in func.__code__.co_varnames:
            print('[SearchAgent] using function ' + fn)
            self.searchFunction = func
        else:
            if heuristic in globals().keys():
                heur = globals()[heuristic]
            elif heuristic in dir(search):
                heur = getattr(search, heuristic)
            else:
                raise AttributeError(heuristic + ' is not a function in searchAgents.py or search.py.')
            print('[SearchAgent] using function %s and heuristic %s' % (fn, heuristic))
            # Note: this bit of Python trickery combines the search algorithm and the heuristic
            self.searchFunction = lambda x: func(x, heuristic=heur)

        # Get the search problem type from the name
        if prob not in globals().keys() or not prob.endswith('Problem'):
            raise AttributeError(prob + ' is not a search problem type in SearchAgents.py.')
        self.searchType = globals()[prob]
        print('[SearchAgent] using problem type ' + prob)

    def registerInitialState(self, state):
        """
        This is the first time that the agent sees the layout of the game
        board. Here, we choose a path to the goal. In this phase, the agent
        should compute the path to the goal and store it in a local variable.
        All of the work is done in this method!

        state: a GameState object (pacman.py)
        """
        if self.searchFunction == None: raise Exception("No search function provided for SearchAgent")
        starttime = time.time()
        problem = self.searchType(state) # Makes a new search problem
        self.actions  = self.searchFunction(problem) # Find a path
        totalCost = problem.getCostOfActions(self.actions)
        print('Path found with total cost of %d in %.1f seconds' % (totalCost, time.time() - starttime))
        if '_expanded' in dir(problem): print('Search nodes expanded: %d' % problem._expanded)

    def getAction(self, state):
        """
        Returns the next action in the path chosen earlier (in
        registerInitialState).  Return Directions.STOP if there is no further
        action to take.

        state: a GameState object (pacman.py)
        """
        if 'actionIndex' not in dir(self): self.actionIndex = 0
        i = self.actionIndex
        self.actionIndex += 1
        if i < len(self.actions):
            return self.actions[i]
        else:
            return Directions.STOP

class PositionSearchProblem(search.SearchProblem):
    """
    Задача поиска - определяет пространство состояний, начальное состояние, 
    тест цели, функцию преемника и функцию стоимости. Эту задачу поиска можно
    использовать для поиска путей к определенной точке на схеме игры pacman.

    Пространство состояний состоит из координат (x, y) позиций в игре pacman.

    Примечание: задача поиска полностью определена; вы НЕ должны менять её код.
    
    """

    def __init__(self, gameState, costFn = lambda x: 1, goal=(1,1), start=None, warn=True, visualize=True):
        """
        Stores the start and goal.

        gameState: A GameState object (pacman.py)
        costFn: A function from a search state (tuple) to a non-negative number
        goal: A position in the gameState
        """
        self.walls = gameState.getWalls()
        self.startState = gameState.getPacmanPosition()
        if start != None: self.startState = start
        self.goal = goal
        self.costFn = costFn
        self.visualize = visualize
        if warn and (gameState.getNumFood() != 1 or not gameState.hasFood(*goal)):
            print('Warning: this does not look like a regular search maze')

        # For display purposes
        self._visited, self._visitedlist, self._expanded = {}, [], 0 # DO NOT CHANGE

    def getStartState(self):
        return self.startState

    def isGoalState(self, state):
        isGoal = state == self.goal

        # For display purposes only
        if isGoal and self.visualize:
            self._visitedlist.append(state)
            import __main__
            if '_display' in dir(__main__):
                if 'drawExpandedCells' in dir(__main__._display): #@UndefinedVariable
                    __main__._display.drawExpandedCells(self._visitedlist) #@UndefinedVariable

        return isGoal

    def getSuccessors(self, state):
        """
        Returns successor states, the actions they require, and a cost of 1.

         As noted in search.py:
             For a given state, this should return a list of triples,
         (successor, action, stepCost), where 'successor' is a
         successor to the current state, 'action' is the action
         required to get there, and 'stepCost' is the incremental
         cost of expanding to that successor
        """

        successors = []
        for action in [Directions.NORTH, Directions.SOUTH, Directions.EAST, Directions.WEST]:
            x,y = state
            dx, dy = Actions.directionToVector(action)
            nextx, nexty = int(x + dx), int(y + dy)
            if not self.walls[nextx][nexty]:
                nextState = (nextx, nexty)
                cost = self.costFn(nextState)
                successors.append( ( nextState, action, cost) )

        # Bookkeeping for display purposes
        self._expanded += 1 # DO NOT CHANGE
        if state not in self._visited:
            self._visited[state] = True
            self._visitedlist.append(state)

        return successors

    def getCostOfActions(self, actions):
        """
        Returns the cost of a particular sequence of actions. If those actions
        include an illegal move, return 999999.
        """
        if actions == None: return 999999
        x,y= self.getStartState()
        cost = 0
        for action in actions:
            # Check figure out the next state and see whether its' legal
            dx, dy = Actions.directionToVector(action)
            x, y = int(x + dx), int(y + dy)
            if self.walls[x][y]: return 999999
            cost += self.costFn((x,y))
        return cost

class StayEastSearchAgent(SearchAgent):
    """
    An agent for position search with a cost function that penalizes being in
    positions on the West side of the board.

    The cost function for stepping into a position (x,y) is 1/2^x.
    """
    def __init__(self):
        self.searchFunction = search.uniformCostSearch
        costFn = lambda pos: .5 ** pos[0]
        self.searchType = lambda state: PositionSearchProblem(state, costFn, (1, 1), None, False)

class StayWestSearchAgent(SearchAgent):
    """
    An agent for position search with a cost function that penalizes being in
    positions on the East side of the board.

    The cost function for stepping into a position (x,y) is 2^x.
    """
    def __init__(self):
        self.searchFunction = search.uniformCostSearch
        costFn = lambda pos: 2 ** pos[0]
        self.searchType = lambda state: PositionSearchProblem(state, costFn)

def manhattanHeuristic(position, problem, info={}):
    "The Manhattan distance heuristic for a PositionSearchProblem"
    xy1 = position
    xy2 = problem.goal
    return abs(xy1[0] - xy2[0]) + abs(xy1[1] - xy2[1])

def euclideanHeuristic(position, problem, info={}):
    "The Euclidean distance heuristic for a PositionSearchProblem"
    xy1 = position
    xy2 = problem.goal
    return ( (xy1[0] - xy2[0]) ** 2 + (xy1[1] - xy2[1]) ** 2 ) ** 0.5

#####################################################
# Эта часть не заполнена. Время писать код!         #
#####################################################

class CornersProblem(search.SearchProblem):
    """
    Эта задача поиска находит пути через все четыре угла схемы игры.

     Вы должны выбрать подходящее пространство состояний и функцию-преемник.
    
    """

    def __init__(self, startingGameState):
        """
        Хранит стены, исходную позицию Пакмана и углы.
        
        """
        self.walls = startingGameState.getWalls()
        self.startingPosition = startingGameState.getPacmanPosition()
        top, right = self.walls.height-2, self.walls.width-2
        self.corners = ((1,1), (1,top), (right, 1), (right, top))
        for corner in self.corners:
            if not startingGameState.hasFood(*corner):
                print('Warning: no food in corner ' + str(corner))
        self._expanded = 0 # НЕ МЕНЯЙТЕ; Количество раскрытых поисковых узлов
        # Пожалуйста, добавьте сюда любой код, который вы хотели бы использовать
        # при инициализации задачи
        "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"

    def getStartState(self):
        """
        Возвращает начальное состояние (в вашем пространстве состояний, а 
        неполное состояние пространства игры Pacman)
        """
        "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
        Проверяет, является ли это состояние поиска целевым состоянием задачи.
        """
        "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
        Возвращает состояния-преемники, действия,  и стоимость 1.

          Как отмечено в search.py:
             Для данного состояния возвращает список из триплетов (successor,
             action, stepCost), где 'successor' - это преемник текущего состояния,
             'action' - это действие, необходимое для его достижения, 
             'stepCost' - затраты для шага перхода к этому преемнику.  
        """

        successors = []
        for action in [Directions.NORTH, Directions.SOUTH, Directions.EAST, Directions.WEST]:
            # Добавьте состояние-приемник в список приемников, если действие является 
            # допустимым
            # Ниже фрагмент кода, который проверяет, не попадает ли новая позиция на
            # стену лабиринта:
            #   x,y = currentPosition
            #   dx, dy = Actions.directionToVector(action)
            #   nextx, nexty = int(x + dx), int(y + dy)
            #   hitsWall = self.walls[nextx][nexty]

            "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"

        self._expanded += 1 # НЕ МЕНЯЙТЕ!
        return successors

    def getCostOfActions(self, actions):
        """
        Возвращает стоимость определенной последовательности действий. Если эти 
        действия включают недопустимый ход, вщзвращает 999999. 
        """
        if actions == None: return 999999
        x,y= self.startingPosition
        for action in actions:
            dx, dy = Actions.directionToVector(action)
            x, y = int(x + dx), int(y + dy)
            if self.walls[x][y]: return 999999
        return len(actions)


def cornersHeuristic(state, problem):
    """
    Эвристика для задачи поиска углов, которую необходимо определить.

       state: текущее состояние поиска
             (структура данных, которую вы выбрали в своей поисковой задаче)

       problem: экземпляр CornersProblem для схемы лабиринта.

     Эта функция всегда должна возвращать число, которое является нижней границей
     кратчайшего пути от состояния к цели задачи; т.е. она должна быть
     допустимой (а также монотонной).
     
    """
    corners = problem.corners # Координаты углов
    walls = problem.walls # Стены лабиринта в виде объекта Grid (game.py)
    "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
    return 0 # Default to trivial solution

class AStarCornersAgent(SearchAgent):
    "Агент SearchAgent  для FoodSearchProblem, использующий A*-поиск и  foodHeuristic"
    def __init__(self):
        self.searchFunction = lambda prob: search.aStarSearch(prob, cornersHeuristic)
        self.searchType = CornersProblem

class FoodSearchProblem:
    """
    Задача поиска, связанная с поиском пути ко всем точкам еды
    в игре Pacman.

    Состояние поиска в этой задаче - это кортеж (pacmanPosition, foodGrid),
    где pacmanPosition: кортеж (x, y) целых чисел, определяющий позицию Pacman. 
    FoodGrid: Grid (см. game.py) со значениями либо True либо False, 
    указывающими наличие оставшейся еды
    """
    def __init__(self, startingGameState):
        self.start = (startingGameState.getPacmanPosition(), startingGameState.getFood())
        self.walls = startingGameState.getWalls()
        self.startingGameState = startingGameState
        self._expanded = 0 # НЕ МЕНЯЙТЕ
        self.heuristicInfo = {} # Словарь эвристики для хранения информации

    def getStartState(self):
        return self.start

    def isGoalState(self, state):
        return state[1].count() == 0

    def getSuccessors(self, state):
        "Возвращает состояния-преемники, действия,  и стоимость 1."
        successors = []
        self._expanded += 1 # DO NOT CHANGE
        for direction in [Directions.NORTH, Directions.SOUTH, Directions.EAST, Directions.WEST]:
            x,y = state[0]
            dx, dy = Actions.directionToVector(direction)
            nextx, nexty = int(x + dx), int(y + dy)
            if not self.walls[nextx][nexty]:
                nextFood = state[1].copy()
                nextFood[nextx][nexty] = False
                successors.append( ( ((nextx, nexty), nextFood), direction, 1) )
        return successors

    def getCostOfActions(self, actions):
        """Возвращает стоимость определенной последовательности действий. Если эти 
        действия включают недопустимый ход, вщзвращает 999999.""" 
        x,y= self.getStartState()[0]
        cost = 0
        for action in actions:
            # figure out the next state and see whether it's legal
            dx, dy = Actions.directionToVector(action)
            x, y = int(x + dx), int(y + dy)
            if self.walls[x][y]:
                return 999999
            cost += 1
        return cost

class AStarFoodSearchAgent(SearchAgent):
    "Агент SearchAgent для FoodSearchProblem, использующий A*-поиск и вашу foodHeuristic"
    def __init__(self):
        self.searchFunction = lambda prob: search.aStarSearch(prob, foodHeuristic)
        self.searchType = FoodSearchProblem

def foodHeuristic(state, problem):
    """
    вристика для FoodSearchProblem,которую вы должны определитьь.

    Эта эвристика должна быть монотонной, чтобы гарантировать правильность.
    Сначала попробуйте придумать допустимую эвристику; почти все допустимые 
    эвристики также будут согласованными (монотонными).

    Если при использовании A*-поиска будет найдено решение, которое хуже, чем поиск
    с равной стоимостью, ваша эвристика  немонотонная и, вероятно, недопустима! 
    С другой стороны, недопустимые или немонотонные эвристики могут найти 
    оптимальные решения, поэтому внимательны.
    
    Состояние - это кортеж (pacmanPosition, foodGrid), где foodGrid - 
    это Grid (см. game.py) со значениями True или False. Вместо этого 
    вы можете вызвать foodGrid.asList (), чтобы получить список координат еды.

    Если вам нужен доступ к такой информации, как стены, гранулы и т. п., 
    Вы можете обратиться problem. Например, problem.walls вернет вам Crid c   
    расположением стен.

    Если вы хотите сохранить информацию для повторного использования в других
    вызовах heuristic, вы можете использовать словарь problem.heuristicInfo.
    Например, если вы хотите сосчитать стены только один раз и сохранить
    значение, используйте: problem.heuristicInfo ['wallCount']=problem.walls.count()
    Последующие вызовы этой эвристики могут получить доступ к этой информации
    issue.heuristicInfo ['wallCount']
    """
    position, foodGrid = state
    "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
    return 0

class ClosestDotSearchAgent(SearchAgent):
    " Поиск еды с помощью последовательных поисков"
    def registerInitialState(self, state):
        self.actions = []
        currentState = state
        while(currentState.getFood().count() > 0):
            nextPathSegment = self.findPathToClosestDot(currentState) # The missing piece
            self.actions += nextPathSegment
            for action in nextPathSegment:
                legal = currentState.getLegalActions()
                if action not in legal:
                    t = (str(action), str(currentState))
                    raise Exception('findPathToClosestDot returned an illegal move: %s!\n%s' % t)
                currentState = currentState.generateSuccessor(0, action)
        self.actionIndex = 0
        print('Path found with cost %d.' % len(self.actions))

    def findPathToClosestDot(self, gameState):
        """
        Возвращает путь (список действий) к ближайшей точке, начиная с
        gameState.
        """
        # Несколько полезных элементов startState
        startPosition = gameState.getPacmanPosition()
        food = gameState.getFood()
        walls = gameState.getWalls()
        problem = AnyFoodSearchProblem(gameState)
   
        "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
        util.raiseNotDefined()

class AnyFoodSearchProblem(PositionSearchProblem):
    """
    Задача поиска пути к любой еде.

     Эта задача поиска аналогична задаче PositionSearchProblem, но имеет другой 
     тест цели, который вам необходимо заполнить ниже. Пространство состояний
     и функцию-преемник изменять не нужно.

     Определение класса (см.выше) AnyFoodSearchProblem (PositionSearchProblem),
     наследует методы PositionSearchProblem.

     Вы можете использовать эту задачу поиска, для заполнения кода 
     метода findPathToClosestDot.
        
    """

    def __init__(self, gameState):
        "Хранит информацию из gameState. Вам не нужно менять этот код"
        # Store the food for later reference
        self.food = gameState.getFood()

        # Store info for the PositionSearchProblem (no need to change this)
        self.walls = gameState.getWalls()
        self.startState = gameState.getPacmanPosition()
        self.costFn = lambda x: 1
        self._visited, self._visitedlist, self._expanded = {}, [], 0 # DO NOT CHANGE

    def isGoalState(self, state):
        """
        Состояние (state) - это позиция Pacman. Заполните кодом проверки цели 
        """
        x,y = state

        "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
        util.raiseNotDefined()

def mazeDistance(point1, point2, gameState):
    """
    Возвращает расстояние  между любыми двумя точками, используя уже созданные
    вами функции поиска. GameState может быть любым игровым состоянием - позиция 
    Pacman в этом состоянии игнорируется.

     Пример использования: mazeDistance ((2,4), (5,6), gameState)

     Может быть полезной вспомогательной функцией для вашего 
     ApproximateSearchAgent.
    
    """
    x1, y1 = point1
    x2, y2 = point2
    walls = gameState.getWalls()
    assert not walls[x1][y1], 'point1 is a wall: ' + str(point1)
    assert not walls[x2][y2], 'point2 is a wall: ' + str(point2)
    prob = PositionSearchProblem(gameState, start=point1, goal=point2, warn=False, visualize=False)
    return len(search.bfs(prob))
