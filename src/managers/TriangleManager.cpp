#include "TriangleManager.hpp"

TriangleManager::TriangleManager(sf::Window& window, Shader& shader) : window(window), shader(shader) {

};

TriangleManager::~TriangleManager() {
    for (int i = 0; i < triangles.size(); ++i) {
        delete triangles[i];
    }
}

triangle* TriangleManager::addTriangle(const GLfloat vertices[]) {
    triangle* t = new triangle(vertices);
    triangles.push_back(t);
    return t;
}


void TriangleManager::render(glm::mat4 &mvp) {
    for (int i = 0; i < triangles.size(); ++i) {
        triangles[i]->draw(mvp, shader);
    }
    shader.Use();
};
