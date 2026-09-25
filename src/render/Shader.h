#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Shader {
public:
    Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    ~Shader();

    void use() const;
    void setUniform1i(const std::string& name, int value) const;
    void setUniform1f(const std::string& name, float value) const;
    void setUniform3f(const std::string& name, float x, float y, float z) const;

private:
    GLuint program;
};

#endif // SHADER_H