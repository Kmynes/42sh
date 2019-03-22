.PHONY: all check doc

all:
	mkdir -p ./build
	cd ./build && cmake .. && make
unit:
	$(MAKE) -s all
	clear
	python3 tests/test_unit.py -c unit

doc:
	doxygen doxy-config

check:
	$(MAKE) -s unit
	python3 tests/test_suite.py --debug
