all: tet cl

tet: build/main.o build/foo.o 
	g++ build/main.o build/foo.o -o tet -lsfml-graphics -lsfml-window -lsfml-system
build/main.o: src/main.cpp
	g++ -Wall -Werror -o build/main.o -c src/main.cpp
build/foo.o: src/foo.cpp
	g++ -Wall -Werror -o build/foo.o -c src/foo.cpp  
cl: 
	clear
clean:
	rm -rf build/* tet 