.PHONY: all check doc

all:
	./autogen.sh

unit:
	$(MAKE) -s all
	clear
	./build/test_42sh

doc:
	doxygen doxy-config

test:
	$(MAKE) -s unit
	python tests/test_suite.py

check_docker:
	$(MAKE) -s all
	./build/test_42sh
	python tests/test_suite.py

check:
	docker-compose --file tests/docker-compose.yml build 42sh_arch
	docker-compose --file tests/docker-compose.yml run --rm 42sh_arch