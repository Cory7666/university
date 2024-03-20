PYTHON ?= /usr/bin/python

strings:
	${PYTHON} 01_strings.py

lists:
	${PYTHON} 02_lists.py

dicts:
	${PYTHON} 03_dicts.py

list_comp:
	${PYTHON} 04_list_comp.py

quick_sort:
	${PYTHON} 05_qsort.py

autograder:
	podman run \
		-v ./extra/codingdiagnostic_r/codingdiagnostic:/code \
		--rm -ti python:3.8 \
		bash -c "cd /code && python autograder.py"
