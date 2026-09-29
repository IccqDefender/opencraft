#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

Shader Shader::fromFiles(const std::string& vertexPath, const std::string& fragmentPath){
    std::string vertexSource = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);
    return Shader(vertexSource, fragmentSource);
}

std::string Shader::readFile(const std::string& path){
    std::ifstream file(path);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open shader file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource){
    m_program = createProgram(vertexSource, fragmentSource);
}

Shader::~Shader(){
    release();
}

Shader::Shader(Shader&& other) noexcept
    : m_program(other.m_program)
    , m_uniformCache(std::move(other.m_uniformCache))
    {
        other.m_program = 0;
    }

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this != &other){
        release();
        m_program = other.m_program;
        m_uniformCache = std::move(other.m_uniformCache);
        other.m_program = 0;
    }
    return *this;
}

void Shader::release() {
    if(m_program != 0){
        glDeleteProgram(m_program);
    }
}

GLuint Shader::compileShader(GLenum type, const std::string& src, const std::string& debugName){
    GLuint shader = glCreateShader(type);
    const char* sourcePtr = src.c_str();
    glShaderSource(shader, 1, &sourcePtr, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success){
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error("Shader compilation failed (" + debugName + "):\n" + infoLog + "\n");
    }

    return shader;
}

GLuint Shader::createProgram(const std::string& vertexSource, const std::string& fragmentSource){
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource, "vertex");
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource, "fragment");

    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success){
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "Shader program linking failed:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Shader::use() const{
    glUseProgram(m_program);
}

GLint Shader::getUniformLocation(const std::string& name){
    auto it = m_uniformCache.find(name);
    if (it != m_uniformCache.end()) {
        return it->second;
    }

    GLint location = glGetUniformLocation(m_program, name.c_str());
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' not found in shader\n";
    }

    m_uniformCache[name] = location;

    return location;
}



void Shader::setBool(const std::string& name, bool value){
    glUniform1i(getUniformLocation(name), (int)value);
}

void Shader::setInt(const std::string& name, int value){
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value){
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value){
    glUniform2fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value){
    glUniform3fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value){
    glUniform4fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& value){
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value){
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

