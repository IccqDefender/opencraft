#pragma once

#include "Texture.h"

#include <memory>
#include <array>

#include <glm/glm.hpp>

class TextureAtlas {
public:
    TextureAtlas(const std::string& path, int tilesPerRow);

    void bind(GLuint uint = 0) const;

    std::array<glm::vec2, 4> getTileUV(glm::ivec2 tile) const;

private:
    std::unique_ptr<Texture> m_texture;
    int m_tilesPerRow;
    float m_tileSize;
};