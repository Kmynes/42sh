.PHONY: all check

all:
	./autogen.sh

check:
	$(MAKE) -s all
	clear
	./build/test_42sh