#pragma once

#include <glad/glad.h>
#include <string>

class Texture {
public:
    explicit Texture(const std::string& path, bool pixelated = true);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void bind(GLuint unit = 0) const;

    int getWidth() const { return m_width; };
    int getHeight() const { return m_height; };

private:
    void release();

    GLuint m_id = 0;

    int m_width = 0;
    int m_height = 0;

    int m_channels = 0;
};