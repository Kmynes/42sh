.PHONY: all check

all:
	./autogen.sh

unit:
	$(MAKE) -s all
	clear
	./build/test_42sh
test:
	$(MAKE) -s unit
	python3 tests/test_suite.py

check_docker:
	$(MAKE) -s all
	./build/test_42sh
	python3 tests/test_suite.py

check:
	docker-compose --file tests/docker-compose.yml build 42sh_arch
	docker-compose --file tests/docker-compose.yml run --rm 42sh_arch