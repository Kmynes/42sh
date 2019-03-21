.PHONY: all check doc

all:
	./autogen.sh

unit:
	$(MAKE) -s all
	clear
	python3 tests/test_suite.py -c unit

doc:
	doxygen doxy-config

test:
	$(MAKE) -s unit
	python3 tests/test_suite.py --debug

check:
	docker-compose --file tests/docker-compose.yml build 42sh_arch
	docker-compose --file tests/docker-compose.yml run --rm 42sh_arch