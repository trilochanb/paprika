CC=g++

build/pomusi:main.cpp
	mkdir -p build/
	${CC} -o $@ $<

clean:
	rm -rf build/
