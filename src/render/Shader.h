#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader{
public:
    static Shader fromFiles(const std::string& vertexPath, const std::string& fragmentPath);

    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator = (Shader&& other) noexcept;

    void use() const;

    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec2(const std::string& name, const glm::vec2& value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec4(const std::string& name, const glm::vec4& value);
    void setMat3(const std::string& name, const glm::mat3& value);
    void setMat4(const std::string& name, const glm::mat4& value);

private:
    GLuint compileShader(GLenum type, const std::string& src, const std::string& debugName);
    GLuint createProgram(const std::string& vertexSource, const std::string& fragmentSource);
    GLint getUniformLocation(const std::string& name);

    void release();

    static std::string readFile(const std::string& path);

    GLuint m_program = 0;

    std::unordered_map<std::string, GLint> m_uniformCache;
};

#endif // SHADER_H