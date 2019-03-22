.PHONY: all check doc

all:
	mkdir -p build
	cmake -B build -S .
	ls build
	$(MAKE) -C build default_target

unit:
	$(MAKE) -s all
	clear
	python3 tests/test_unit.py -c unit

doc:
	doxygen doxy-config

check:
	$(MAKE) -s unit
	python3 tests/test_suite.py --debug
