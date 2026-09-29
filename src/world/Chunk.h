#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Block.h"

class Mesh;
class Shader;

class Chunk{
public:
    static constexpr int SIZE_X = 16;
    static constexpr int SIZE_Y = 64;
    static constexpr int SIZE_Z = 16;

    explicit Chunk(glm::ivec3 chunckPosition);

    Block getBlock(int x, int y, int z) const;
    void setBlock(int x, int y, int z, BlockType type);

    void generateMesh();
    void draw(Shader& shader) const;

    glm::ivec3 getPosition() const { return m_position; };
    glm::vec3 getWorldPosition() const;

    bool isDirty() const { return m_dirty; };

private:
    int index(int x, int y, int z) const;
    bool isInBounds(int x, int y, int z) const;
    bool isFaceVisible(int x, int y, int z) const;

    glm::ivec3 m_position;

    std::vector<Block> m_blocks;
    std::unique_ptr<Mesh> m_mesh;
    bool m_dirty = true;

};