
build/bin: build/main.o build/perm.o
	clang++ -o build/bin -std=c++17 -O3 -g build/main.o build/perm.o

build/main.o: src/main.cpp
	clang++ -c -std=c++17 -O3 src/main.cpp -o build/main.o

build/perm.o: src/perm.cpp
	clang++ -c -std=c++17 -O3 src/perm.cpp  -o build/perm.o

run:
	build/bin

clean:
	rm -rf build/*.o build/bin
