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
import util
from game import Directions
from typing import Tuple, List, Union, Any


class SearchProblem:
    """
    Этот класс описывает структуру задачи поиска, но не реализует 
    ни один из методов (в объектно-ориентированной терминологии: абстрактный класс).

     Вам не нужно ничего менять в этом классе.
    """

    def getStartState(self) -> Tuple[int, int]:
        """
        Возвращает начальное состояние для задачи поиска.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: состоние

        Возвращает True, когда состояние является допустимым целевым состоянием.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state) -> List[Tuple[Tuple[int, int], str, float]]:
        """
          state: состояние

        Для данного состояния возвращает список из триплетов (successor,
        action, stepCost), где 'successor' - это преемник текущего
        состояния, 'action' - это действие, необходимое для этого, а "stepCost" - 
        затраты раскрытия преемника.

        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions:Список действий, которые нужно предпринять

         Этот метод возвращает общую стоимость определенной последовательности
         действий. Последовательность должна состоять из разрешенных ходов.
        """
        util.raiseNotDefined()


@dataclass(eq=False)
class RootNode:
    state: Tuple[int, int]

    def make_child(self, state, action, cost):
        return Node(parent=self, state=state,
                    action=action,
                    cost=cost)

    def __eq__(self, __value: object) -> bool:
        return (__value.state
                if isinstance(__value, RootNode)
                else __value) == self.state


@dataclass(eq=False)
class Node(RootNode):
    action: str
    cost: float
    parent: RootNode

    def make_child(self, state, action, cost):
        return super().make_child(state, action, self.cost + cost)

    def rewrite_info_from(self, other: 'Node'):
        self.parent = other.parent
        self.action = other.action
        self.cost = other.cost


class AdvancedStack(util.Stack):
    def __iter__(self):
        for item in self.list:
            yield item

    def __contains__(self, item):
        return item in self.list

    def get(self, item: RootNode):
        nodes = [node for node in self.list if item == node]
        return nodes[0] if len(nodes) != 0 else None


class AdvancedQueue(util.Queue):
    def __iter__(self):
        for item in self.list:
            yield item

    def __contains__(self, item):
        return item in self.list


class AdvancedPriorityQueue(util.PriorityQueue):
    def push(self, item: RootNode, h_value: float = 0):
        return super().push(item, h_value)

    def update(self, item: RootNode, h_value: float = 0):
        return super().update(item, h_value)

    def get(self, item: RootNode):
        nodes = [node[2] for node in self.heap if node[2] == item]
        return nodes[0] if len(nodes) != 0 else None

    def __contains__(self, __value):
        return self.get(__value) != None


def tinyMazeSearch(problem: SearchProblem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    s = Directions.SOUTH
    w = Directions.WEST
    return [s, s, w, s, w, w, s, w]


def _search_path_core(problem: SearchProblem,
                      states_opened: Union[AdvancedStack, AdvancedQueue,
                                           AdvancedPriorityQueue]):
    states_closed = AdvancedStack()
    ret = AdvancedQueue()
    found = False

    node: RootNode = RootNode(problem.getStartState())
    states_opened.push(node)

    while not (found or states_opened.isEmpty()):
        node = states_opened.pop()
        # print('Analize:', node.state)
        if problem.isGoalState(node.state):
            found = True
        else:
            states_closed.push(node.state)
            for child in problem.getSuccessors(node.state):
                child_node = node.make_child(child[0], child[1], child[2])
                # Добавить узел в массив раскрываемых только в том случае,
                # если этот узел не был раскрыт ранее и либо очередь является
                # приоритетной (т.к. в любом случае более выгодный узел по
                #  стоимости будет раскрыт раньше менее выгодного), либо
                # наличие в списке раскрываемых (чтобы избежать рекурсии)
                if ((child_node not in states_closed)
                    and (isinstance(states_opened, AdvancedPriorityQueue)
                         or (child_node not in states_opened))):
                    states_opened.push(child_node)

    if found:
        while isinstance(node, Node):
            ret.push(node.action)
            node = node.parent

    return list(ret)


def _search_path_core_a(problem: SearchProblem, heuristic):
    states_closed = []
    result = AdvancedQueue()
    states_opened = AdvancedPriorityQueue()
    node = RootNode(problem.getStartState())
    states_opened.push(node, heuristic(node.state, problem))
    found = False

    while (not states_opened.isEmpty()) and (not found):
        node: RootNode = states_opened.pop()
        if problem.isGoalState(node.state):
            found = True
        else:
            states_closed.append(node)
            for successor_node in [
                    node.make_child(suc[0], suc[1], suc[2])
                    for suc in problem.getSuccessors(node.state)]:
                h = heuristic(successor_node.state, problem)

                # h(parent) <= h(successor) + c(parent, successor)
                monotonic_case = heuristic(node.state, problem) <= (
                    h + (successor_node.cost -
                         (node.cost if isinstance(node, Node) else 0)))

                if successor_node in states_closed:
                    old_node = [item for item in states_closed
                                if item == successor_node][0]
                    if isinstance(old_node, Node) \
                        and (successor_node.cost < old_node.cost):
                        states_closed.remove(old_node)
                        old_node.rewrite_info_from(successor_node)
                        states_opened.update(old_node, successor_node.cost+h)

                elif successor_node in states_opened:
                    old_node = states_opened.get(successor_node)
                    if isinstance(old_node, Node) \
                        and (successor_node.cost < old_node.cost):
                        old_node.rewrite_info_from(successor_node)
                        states_opened.update(old_node, successor_node.cost+h)
                else:
                    states_opened.push(successor_node, successor_node.cost+h)

    if found:
        while isinstance(node, Node):
            result.push(node.action)
            node = node.parent

    return list(result)


def depthFirstSearch(problem: SearchProblem):
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
    return _search_path_core(problem, AdvancedStack())


def breadthFirstSearch(problem: SearchProblem):
    start_state = problem.getStartState()
    visited, path = [], []
    state_queue = AdvancedQueue()
    state_queue.push((start_state, []))

    while not state_queue.isEmpty():
        actual_state, path = state_queue.pop()

        if problem.isGoalState(actual_state):
            return path

        if actual_state not in visited:
            adjacent = problem.getSuccessors(actual_state)
        
            for adjacent in adjacent:
                state = adjacent[0]
                if state not in visited:
                    action = adjacent[1]
                    state_queue.push((state, path + [action]))
            visited.append(actual_state)
    return path


def uniformCostSearch(problem: SearchProblem):
    """Находит узел минимальной стоимости """
    "*** ВСТАВЬТЕ ВАШ КОД СЮДА ***"
    return _search_path_core(problem, AdvancedPriorityQueue())


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
    return _search_path_core_a(problem, heuristic)


# Аббривиатуры
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
