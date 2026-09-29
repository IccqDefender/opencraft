#pragma once

#include "Block.h"
#include <array>

class BlockRegistry{
public:
    static void initialize();

    static const BlockProperties& get(BlockType type);

private:
    static std::array<BlockProperties, (size_t)BlockType::Count> s_properties;
    static bool s_initialized;
};