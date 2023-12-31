CC=g++
BINARY=paprika

setup:
	mkdir -p build/

build/audio.o: src/audio/audio.cpp
	${CC} -c $< -o $@ -lSDL2

build/utils.o: src/utils/utils.cpp
	${CC} -c $< -o $@

build/pomodoro.o: src/pomodoro/pomodoro.cpp
	${CC} -c $< -o $@

build/${BINARY}: src/main.cpp build/audio.o build/utils.o build/pomodoro.o
	mkdir -p build/
	${CC} -o $@ $^ -lSDL2

build: setup build/audio.o build/utils.o build/pomodoro.o build/${BINARY}

clean:
	rm -rf build/

uninstall:
	sudo rm -f /usr/bin/${BINARY}

install: build/${BINARY}
	sudo cp $< /usr/bin/
	@make clean

