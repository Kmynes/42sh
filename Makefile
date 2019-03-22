.PHONY: all check doc

all:
	./build.sh

unit:
	$(MAKE) -s all
	clear
	python3 tests/test_unit.py -c unit

doc:
	doxygen doxy-config

check:
	$(MAKE) -s unit
	python3 tests/test_suite.py --debug
