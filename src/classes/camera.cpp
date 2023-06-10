#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, Shader &shader, float &time) : _shader(shader), _time(time) {
    projection = glm::perspective(glm::radians(fov), (float) 1.f / (float) 1.f, 0.1f, 100.0f);
    camera_pos = glm::vec3(0, 0, 1);
    view = glm::lookAt(
        camera_pos, // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

void Camera::translate(glm::vec3 vector) {
    view = view * glm::translate(glm::mat4(1.0f), vector);
}

void Camera::scale(glm::vec3 vector) {
    view = view * glm::scale(glm::mat4(1.0f), vector);
}

// void Camera::zoom(glm::vec3 vector, float time) {
//     // Implement zooming logic here
//     // Update the camera position and recalculate the view matrix if necessary
// }

// void Camera::move(glm::vec3 vector, float time) {
//     // Implement camera movement logic here
//     // Update the camera position and recalculate the view matrix if necessary
// }

// void Camera::loop() {
//     // Main camera loop logic
//     // You can update the camera's parameters based on input or time here
// }