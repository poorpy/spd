STD = "c++14"

bin: build/main.o build/io.o build/data.o build/schrage.o
	clang++ -o bin -std=${STD} -g -O3 build/*

build/main.o: main.cpp
	clang++ -o build/main.o -std=${STD} -g -O3 -c main.cpp

build/io.o: src/io.cpp
	clang++ -o build/io.o -std=${STD} -g -O3 -c src/io.cpp

build/data.o: src/data.cpp
	clang++ -o build/data.o -std=${STD} -g -O3 -c src/data.cpp

build/schrage.o: src/schrage.cpp
	clang++ -o build/schrage.o -std=${STD} -g -O3 -c src/schrage.cpp

clean:
	rm -rf bin build/*
