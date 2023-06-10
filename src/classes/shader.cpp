#include "shader.hpp"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertex, const char* frag)
{
    programID = CreateShaderProgram(vertex, frag);
}

Shader::~Shader()
{
    glDeleteProgram(programID);
}

void Shader::Use()
{
    glUseProgram(programID);
}

void Shader::SetFloat(const char* name, float value)
{
    GLint location = glGetUniformLocation(programID, name);
    glUniform1f(location, value);
}

void Shader::SetInt(const char* name, int value)
{
    GLint location = glGetUniformLocation(programID, name);
    glUniform1i(location, value);
}

void Shader::Set4fv(const char* name, const glm::mat4& value) {
    GLint location = glGetUniformLocation(programID, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

GLuint Shader::LoadShader(GLenum shaderType, const char* shader)
{

    // Compile shader
    GLuint shaderID = glCreateShader(shaderType);
    const char* shaderCodePtr = shader;
    glShaderSource(shaderID, 1, &shaderCodePtr, nullptr);
    glCompileShader(shaderID);

    // Check for shader compilation errors
    CheckCompileErrors(shaderID, shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");

    return shaderID;
}

GLuint Shader::CreateShaderProgram(const char* vertex, const char* frag)
{
    // Load vertex and fragment shaders
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertex);
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, frag);

    // Create shader program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for shader program linking errors
    CheckCompileErrors(program, "PROGRAM");

    // Delete the individual shaders as they are now linked to the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Shader::CheckCompileErrors(GLuint shader, const char* type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Shader compilation error (" << type << "): " << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Shader program linking error: " << infoLog << std::endl;
        }
    }
}