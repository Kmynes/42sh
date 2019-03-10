.PHONY: all check

all:
	./autogen.sh

test:
	$(MAKE) -s all
	clear
	./build/test_42sh

check_docker:
	$(MAKE) -s all
	./build/test_42sh

check:
	docker-compose --file tests/docker-compose.yml build 42sh_arch
	docker-compose --file tests/docker-compose.yml run --rm 42sh_arch