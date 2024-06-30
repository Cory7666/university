.PHONY: run-a-star autograde-q4 run-corners

run-depth-first:
	python pacman.py -l tinyMaze \
					 -p SearchAgent \
					 -a fn=depthFirstSearch

run-breadth-first:
	python pacman.py -l tinyMaze \
					 -p SearchAgent \
					 -a fn=breadthFirstSearch

run-uniform-cost-search:
	python pacman.py -l mediumMaze \
					 -p SearchAgent \
					 -a fn=ucs

run-scary-maze:
	python pacman.py -l mediumScaryMaze \
		-p StayWestSearchAgent

run-dotted-maze:
	python pacman.py -l mediumDottedMaze \
		-p StayEastSearchAgent

autograde-q1:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q1"

autograde-q2:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q2"

autograde-q3:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q3"

run-a-star:
	python pacman.py -l bigMaze -z .5 \
					 -p SearchAgent -a fn=astar,heuristic=manhattanHeuristic

autograde-q4:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q4"

run-corners: run-corners-tiny run-corners-medium

run-corners-tiny:
	python pacman.py -l tinyCorners \
					 -p SearchAgent -a fn=bfs,prob=CornersProblem

run-corners-medium:
	python pacman.py -l mediumCorners \
					 -p SearchAgent -a fn=bfs,prob=CornersProblem

autograde-q5:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q5"

run-corners-heuristic:
	python pacman.py -l mediumCorners \
					 -p AStarCornersAgent -z 0.5

autograde-q6:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q6"

run-eat-em-all:
	python pacman.py -l trickySearch \
					 -p AStarFoodSearchAgent

autograde-q7:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q7"

run-greedy-search:
	python pacman.py -l bigSearch \
					 -p ClosestDotSearchAgent -z .5

autograde-q8:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q8"
