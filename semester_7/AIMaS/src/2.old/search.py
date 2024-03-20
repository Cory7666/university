# search.py
# ---------
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
В search.py вам необходимо реализовать общие алгоритмы поиска, которые вызываются
агентом Pacman (в searchAgents.py).
"""

from dataclasses import dataclass
import game
import util

_Successor = tuple[int, int]


class SearchProblem:
    """
    Этот класс описывает структуру задачи поиска, но не реализует 
    ни один из методов (в объектно-ориентированной терминологии: абстрактный класс).

     Вам не нужно ничего менять в этом классе.
    """

    def getStartState(self) -> _Successor:
        """
        Возвращает начальное состояние для задачи поиска.
        """
        ...

    def isGoalState(self, state) -> bool:
        """
          state: состоние

        Возвращает True, когда состояние является допустимым целевым состоянием.
        """
        ...

    def getSuccessors(self, state) -> list[tuple[_Successor, str, int]]:
        """
          state: состояние

        Для данного состояния возвращает список из триплетов (successor,
        action, stepCost), где 'successor' - это преемник текущего
        сосsearch.pyтояния, 'action' - это действие, необходимое для этого, а "stepCost" - 
        затраты раскрытия преемника.
        """
        ...

    def getCostOfActions(self, actions):
        """
         actions:Список действий, которые нужно предпринять

         Этот метод возвращает общую стоимость определенной последовательности
         действий. Последовательность должна состоять из разрешенных ходов.
        """
        ...


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return [s, s, w, s, w, w, s, w]


class AdvancedStack(util.Stack):
    def __contains__(self, item):
        return (item in self.list)

    def __iter__(self):
        for item in self.list:
            yield item


class AdvancedQueue(util.Queue):
    def __contains__(self, item):
        return (item in self.list)

    def __iter__(self):
        for item in self.list:
            yield item


class AdvancedPriorityQueue(util.PriorityQueue):
    def __contains__(self, item):
        return (item in self.heap)

    def __iter__(self):
        for item in self.heap:
            yield item


@dataclass
class AbstractSearchNode:
    state: tuple[int, int]

    def __eq__(self, other):
        print(f"{self} == {other} ?")
        return other.state == self.state


@dataclass(eq=False)
class StartSearchNode(AbstractSearchNode):
    pass


@dataclass(eq=False)
class SearchNode(AbstractSearchNode):
    action: game.Directions
    parent: AbstractSearchNode
    cost: int = 1

    def __lt__(self, other):
        return self.cost < other.cost


@dataclass(eq=False)
class State:
    parent: 'State'
    state: _Successor
    action: str
    cost: int

    @property
    def start_state(self):
        return None == self.parent

    def __eq__(self, __value: object) -> bool:
        return ((__value.state == self.state)
                if isinstance(__value, State)
                else False)


def depthFirstSearch(problem):
    """
    Поиск самого глубокого узла в дереве поиска. 

    Ваш алгоритм поиска должен возвращать список действий, которые 
    ведут к цели. Убедитесь, что реализуете алгоритм поиска на графе

    Прежде чем кодировать,полезно выполнить функцию  с этими простыми
    командами,чтобы понять смысл задачи (problem), передаваемой на вход:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"

    states_open, states_close = AdvancedStack(), AdvancedStack()
    found = False
    node: AbstractSearchNode = None
    ret = []
    states_open.push(StartSearchNode(problem.getStartState()))

    while not found:
        if states_open.isEmpty():
            break

        node = states_open.pop()

        if problem.isGoalState(node.state):
            found = True
        else:
            states_close.push(node)
            for child in problem.getSuccessors(node.state):
                child_node = SearchNode(child[0], child[1], node)
                if ((child_node not in states_close)
                        and (child_node not in states_open)):
                    states_open.push(child_node)
    else:
        while not isinstance(node, StartSearchNode):
            if isinstance(node, SearchNode):
                ret.insert(0, node.action)
                node = node.parent
            else:
                raise TypeError

    return ret


def breadthFirstSearch(problem):
    """Находит самые поверхностные узлы в дереве поиска """
    "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
    states_open, states_close = AdvancedQueue(), AdvancedQueue()
    found = False
    node: AbstractSearchNode = None
    ret = []
    states_open.push(StartSearchNode(problem.getStartState()))

    while not found:
        if states_open.isEmpty():
            break

        node = states_open.pop()

        if problem.isGoalState(node.state):
            found = True
        else:
            states_close.push(node)
            for child in problem.getSuccessors(node.state):
                child_node = SearchNode(child[0], child[1], node)
                if ((child_node not in states_close)
                        and (child_node not in states_open)):
                    states_open.push(child_node)
    else:
        while not isinstance(node, StartSearchNode):
            if isinstance(node, SearchNode):
                ret.insert(0, node.action)
                node = node.parent
            else:
                raise TypeError

    return ret


def uniformCostSearch(problem: SearchProblem):
    """Находит узел минимальной стоимости """
    "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"

    states_open, states_close = AdvancedPriorityQueue(), AdvancedQueue()
    found = False
    node = State(None, problem.getStartState(), game.Directions.STOP, 0)
    ret = AdvancedQueue()
    states_open.push(node, node.cost)

    while (not found) and (not states_open.isEmpty()):
        node: State = states_open.pop()
        if problem.isGoalState(node.state):
            found = True
        else:
            states_close.push(node)
            children = [State(node, raw_child[0], raw_child[1], raw_child[2] + node.cost)
                        for raw_child in problem.getSuccessors(node.state)]
            for child in children:
                if ((child not in states_close) and (child not in states_open)):
                    states_open.push(child, child.cost)

    if found:
        while not node.start_state:
            ret.push(node.action)
            node = node.parent
    print("List:")
    print(list(ret))
    return list(ret)


def nullHeuristic(state, problem=None):
    """
    Эвристическая функция оценивает стоимость от текущего состояния до 
    ближайшей цели в задаче SearchProblem. Эта эвристика тривиальна.
    """
    return 0


def aStarSearch(problem, heuristic=nullHeuristic):
    """
    Находит узел с наименьшей комбинированной стоимостью, включающей эвристику
    """
    "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
    util.raiseNotDefined()


# Аббривиатуры
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
