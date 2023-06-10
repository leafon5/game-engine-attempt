#pragma once

#include "../pch.h"

#include "shader.hpp"

class Camera {
    public:
        Camera(float fov, Shader &shader, float &time);
        void translate(glm::vec3 vector);
        void scale(glm::vec3 vector);
        // void zoom(glm::vec3 vector, float time);
        // void move(glm::vec3 vector, float time);
        // void loop();
        glm::mat4 view;
        glm::mat4 projection;
    private:
        glm::vec3 camera_pos;
        float start_time;
        float &_time;
        Shader &_shader;
};