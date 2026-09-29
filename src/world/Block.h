#pragma once

#include <cstdint>
#include <string>
#include <array>

#include <glm/glm.hpp>

enum class BlockType : uint8_t {
    Air = 0,
    Grass,
    Dirt,
    Stone,
    Sand,
    Water,
    Wood,
    Leaves,

    Count
};

enum class BlockFace {
    Top,
    Bottom,
    North,
    South,
    East,
    West
};

struct BlockProperties {
    std::string name = "air";

    bool isSolid = false;
    bool isTransparent = true;
    bool isOpaque = false;

    std::array<glm::ivec2, 6> faceTiles = {};
};

struct Block {
    BlockType type = BlockType::Air;

    bool isAir() const { return type == BlockType::Air; };
};

