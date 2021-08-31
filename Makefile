all: compile execute

compile:
	g++ main.cpp -o test.exe -DSFML_STATIC -I C:\Users\ferna\Desktop\chess\source\include -L C:\Users\ferna\Desktop\chess\source\lib -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2 -lsfml-network-2 -lsfml-graphics-2 -lopengl32 -lwinmm -lgdi32

execute:
	test.exe