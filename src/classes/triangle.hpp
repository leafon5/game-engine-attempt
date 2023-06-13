#pragma once

#include "../pch.h"
#include "shader.hpp"

class triangle
{
    public: 
        triangle(const GLfloat vertices[]);
        void buffer();
        void draw(glm::mat4 mvp, Shader &shader);
        void move(glm::vec3 vector);
        void place(glm::vec3 point);
        void update(glm::mat4 transformation);
        void setIndex(int i);
        int getIndex();
        glm::vec3 calculateMiddlePoint() const;
        glm::vec3 middle;
        glm::vec3 transformPoint(glm::vec3 point);
    private:
        glm::mat4 model;
        int index;
        glm::vec3 calculateLengths() const;
        glm::vec3 lengths; // lengths between the middle point and the vertex
        GLuint vertexbuffer;
        static const int vertexCount = 9; // Number of vertices
        GLfloat _vertices[vertexCount]; // Define the array with a fixed size
};