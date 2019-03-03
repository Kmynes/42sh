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
	docker-compose run 42sh_arch make check_docker
