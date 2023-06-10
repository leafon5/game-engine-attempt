#pragma once

#include "../pch.h"

class Shader
{
public:
    Shader(const char* vertex, const char* frag);
    ~Shader();

    void Use();
    void SetFloat(const char* name, float value);
    void SetInt(const char* name, int value);
    void Set4fv(const char* name, const glm::mat4& value);

private:
    GLuint programID;

    GLuint LoadShader(GLenum shaderType, const char* shader);
    GLuint CreateShaderProgram(const char* vertex, const char* frag);
    void CheckCompileErrors(GLuint shader, const char* type);
};