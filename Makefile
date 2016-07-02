.PHONY: build

run:
	./build/speedrun

build:
	mkdir -p build
	cd build && cmake .. && make
