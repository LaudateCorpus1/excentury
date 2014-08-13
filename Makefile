# excentury makefile

all: install-user

export:
	git archive --format zip --output excentury.zip master

install:
	python setup.py install

install-user:
	python setup.py install --user

build:
	python setup.py sdist

develop:
	python setup.py develop --user

clean:
	rm -rf excentury.egg-info
	rm -rf build

pypi:
	python setup.py sdist upload
