CC=g++
BINARY=pomusi

build/${BINARY}:main.cpp
	mkdir -p build/
	${CC} -o $@ $<

clean:
	rm -rf build/

uninstall:
	sudo rm -rf /usr/bin/${BINARY}

install:build/pomusi
	sudo cp build/${BINARY} /usr/bin/
	@make clean
