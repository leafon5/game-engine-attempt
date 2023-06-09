#pragma once

#include "../pch.h"
#include <SFML/Window.hpp>

class triangle
{
    public: 
        triangle(const GLfloat vertices[], sf::Window &window);
        void buffer();
        void draw();
    private:
        GLuint vertexbuffer;
        static const int vertexCount = 9; // Number of vertices
        GLfloat _vertices[vertexCount]; // Define the array with a fixed size
        sf::Vector2u windowSize;
};