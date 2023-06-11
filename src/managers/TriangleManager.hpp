#pragma once

#include "../pch.h"
#include "../classes/triangle.hpp"

class TriangleManager {
public:
    TriangleManager(sf::Window& window);

    void addTriangle(const GLfloat vertices[]);
    void updateTriangle(int index, const glm::mat4& modelMatrix);
    void renderTriangles(const glm::mat4& projection, const glm::mat4& view);

private:
    std::vector<triangle> triangles;
    std::vector<glm::mat4> modelMatrices;
    sf::Window& window;

    void updateModelMatrices();
};