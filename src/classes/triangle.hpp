#pragma once

#include "../pch.h"
#include <SFML/Window.hpp>

class triangle
{
    public: 
        triangle(const GLfloat vertices[], sf::Window &window);
        void buffer();
        void draw();
        void move(glm::vec3 vector);
        void place(glm::vec3 point);
        glm::vec3 calculateMiddlePoint() const;
        glm::vec3 middle;
    private:
        glm::vec3 calculateLengths() const;
        glm::vec3 lengths; // lengths between the middle point and the vertex
        GLuint vertexbuffer;
        static const int vertexCount = 9; // Number of vertices
        GLfloat _vertices[vertexCount]; // Define the array with a fixed size
        sf::Vector2u windowSize;
};