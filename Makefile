all: compile link

compile:
	g++ -I include -c src/main.cpp -o build/main.o -DGLEW_STATIC
	g++ -I include -c src/classes/triangle.cpp -o build/triangle.o -DGLEW_STATIC
	g++ -I include -c src/classes/shader.cpp -o build/shader.o -DGLEW_STATIC




link: build/main.o build/triangle.o build/shader.o  src/shaders/shaders.cpp src/pch.h src/classes/triangle.hpp src/classes/shader.hpp 
	g++ build/main.o build/triangle.o build/shader.o -o build/main -L lib -DGLEW_STATIC -lglfw3 -l glew32s -l glu32 -l opengl32 -lglew32s -l sfml-graphics -l sfml-window -l sfml-system