# TODO: remove relative paths for linking headers
text-adv: main.o node.o maze.o
	g++ -std=c++11 -static-libstdc++ main.o node.o maze.o -o maze-gen

main.o: ./src/main.cpp
	g++ -std=c++11 -static-libstdc++ -c ./src/main.cpp

node.o: ./src/node.cpp ./include/node.hpp
	g++ -std=c++11 -static-libstdc++ -c ./src/node.cpp

maze.o: ./src/maze.cpp ./include/maze.hpp
	g++ -std=c++11 -static-libstdc++ -c ./src/maze.cpp

clean: 
	del *.o maze-gen.exe