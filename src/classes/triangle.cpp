#include "triangle.hpp"

triangle::triangle(const GLfloat vertices[], sf::Window& window) {
    windowSize = window.getSize();
    for (int i = 0; i < vertexCount; i += 3) {
        _vertices[i] = vertices[i] / windowSize.x;
        _vertices[i + 1] = vertices[i + 1] / windowSize.y;
        _vertices[i + 2] = vertices[i + 2];
    }
}

void triangle::buffer() {
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
}

void triangle::draw() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}