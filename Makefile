CC=g++
BINARY=pomusi

setup:
	mkdir -p build/

build/audio.o: src/audio/audio.cpp
	${CC} -c $< -o $@ -lSDL2

build/utils.o: src/utils/utils.cpp
	${CC} -c $< -o $@

build/${BINARY}: src/main.cpp build/audio.o build/utils.o
	mkdir -p build/
	${CC} -o $@ $^ -lSDL2

build: setup build/audio.o build/utils.o build/${BINARY}

clean:
	rm -rf build/

uninstall:
	sudo rm -f /usr/bin/${BINARY}

install: build/${BINARY}
	sudo cp $< /usr/bin/
	@make clean

