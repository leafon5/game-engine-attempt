#pragma once

#include "../pch.h"
#include "../classes/triangle.hpp"
#include "../classes/shader.hpp"

class TriangleManager {
public:
    TriangleManager(sf::Window& window, Shader& shader);
    ~TriangleManager();
    triangle *addTriangle(const GLfloat vertices[]);
    void render(glm::mat4 &mvp);

private:
    std::vector<triangle*> triangles;
    sf::Window& window;
    Shader& shader;
};