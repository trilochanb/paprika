CC=g++
BINARY=pomusi

setup:
	mkdir -p build/

build/audio.o: src/audio/audio.cpp
	${CC} -c $< -o $@ -lSDL2

build/${BINARY}: src/main.cpp build/audio.o
	mkdir -p build/
	${CC} -o $@ $^ -lSDL2

build: setup build/audio.o build/${BINARY}

clean:
	rm -rf build/

uninstall:
	sudo rm -f /usr/bin/${BINARY}

install: build/${BINARY}
	sudo cp $< /usr/bin/
	@make clean

