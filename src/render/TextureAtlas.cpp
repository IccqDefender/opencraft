#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const std::string& path, int tilesPerRow)
    : m_tilesPerRow(tilesPerRow)
    , m_tileSize(1.0f / (float)tilesPerRow)
{
    m_texture = std::make_unique<Texture>(path, true);
}

void TextureAtlas::bind(GLuint unit) const {
    m_texture->bind(unit);
}

std::array<glm::vec2, 4> TextureAtlas::getTileUV(glm::ivec2 tile) const {
    float u0 = tile.x * m_tileSize;
    float v0 = tile.y * m_tileSize;

    float u1 = u0 * m_tileSize;
    float v1 = v0 * m_tileSize;

    return { glm::vec2(u0, v0), glm::vec2(u0, v1), glm::vec2(u1, v1), glm::vec2(u1, v0) };
}