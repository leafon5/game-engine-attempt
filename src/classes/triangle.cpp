#include "triangle.hpp"

float calculateDistance(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

triangle::triangle(const GLfloat vertices[]) {
    for (int i = 0; i < vertexCount; i++) {
        _vertices[i] = vertices[i];
    }
    middle = calculateMiddlePoint();
    lengths = calculateLengths();
}

glm::vec3 triangle::calculateMiddlePoint() const {
    glm::vec3 middlePoint;
    middlePoint.x = (_vertices[0] + _vertices[3] + _vertices[6]) / 3.0f;
    middlePoint.y = (_vertices[1] + _vertices[4] + _vertices[7]) / 3.0f;
    middlePoint.z = (_vertices[2] + _vertices[5] + _vertices[8]) / 3.0f;
    return middlePoint;
}

glm::vec3 triangle::calculateLengths() const {
    glm::vec3 _lengths;
    _lengths[0] = calculateDistance(_vertices[0], _vertices[1], middle.x, middle.y);
    _lengths[1] = calculateDistance(_vertices[3], _vertices[4], middle.x, middle.y);
    _lengths[2] = calculateDistance(_vertices[6], _vertices[7], middle.x, middle.y);
    return _lengths;
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

void triangle::move(glm::vec3 vector) {
    _vertices[0] += vector.x;
    _vertices[1] += vector.y;
    _vertices[2] += vector.z;

    _vertices[3] += vector.x;
    _vertices[4] += vector.y;
    _vertices[5] += vector.z;

    _vertices[6] += vector.x;
    _vertices[7] += vector.y;
    _vertices[8] += vector.z;

    buffer();
}

void triangle::place(glm::vec3 point) {
    
    glm::vec3 currentMiddle = calculateMiddlePoint();
    glm::vec3 displacement = point - currentMiddle;

    _vertices[0] += displacement.x;
    _vertices[1] += displacement.y;
    _vertices[2] += displacement.z;

    _vertices[3] += displacement.x;
    _vertices[4] += displacement.y;
    _vertices[5] += displacement.z;

    _vertices[6] += displacement.x;
    _vertices[7] += displacement.y;
    _vertices[8] += displacement.z;

    middle = calculateMiddlePoint();
    buffer();
}
