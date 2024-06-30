autograde-q1:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q1"

autograde-q2:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q2"

autograde-q3:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q3"

autograde-q4:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q4"

autograde-q5:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q5"

autograde-q6:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q6"

autograde-q7:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q7"

autograde-q8:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q8"

autograde-q9:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q9"

autograde-q10:
	podman run -v .:/code --rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py -q q10"

run-qagent-with-approx:
	python pacman.py \
		-p ApproximateQAgent -a extractor=SimpleExtractor \
		-x 50 -n 60 -l mediumGrid

run-first-task:
	python gridworld.py -a value -i 5

run-second-task:
	python gridworld.py -a value -i 100 \
		-g BridgeGrid --discount 0.9 \
		--noise 0.2

run-qlearn:
	python pacman.py -p PacmanQAgent \
		-x 2000 -n 2010 -l smallGrid

run-crawler:
	python crawler.py
