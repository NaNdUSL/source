all: compile execute

compile:
	g++ main.cpp -o test -lsfml-graphics -lsfml-window -lsfml-system

execute:
	./test