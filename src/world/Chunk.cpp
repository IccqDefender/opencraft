#include "Chunk.h"

#include "BlockRegistry.h"

#include "../render/Mesh.h"
#include "../render/Shader.h"
#include "../render/Vertex.h"

#include <glm/gtc/matrix_transform.hpp>

#include <array>

namespace {
    struct FaceDef
    {
        BlockFace face;
        glm::ivec3 normal;
        std::array<glm::vec3, 4> vertices;
    };

    const std::array<FaceDef, 6> FACES = {{
        // TOP (+Y)
        { BlockFace::Top, {0, 1, 0}, {{
            {0, 1, 0}, {0, 1, 1}, {1, 1, 1}, {1, 1, 0}
        }}},
        // BOTTOM (-Y)
        { BlockFace::Bottom, {0, -1, 0}, {{
            {0, 0, 1}, {0, 0, 0}, {1, 0, 0}, {1, 0, 1}
        }}},
        // NORTH (+Z)
        { BlockFace::North, {0, 0, 1}, {{
            {1, 0, 1}, {1, 1, 1}, {0, 1, 1}, {0, 0, 1}
        }}},
        // SOUTH (-Z)
        { BlockFace::South, {0, 0, -1}, {{
            {0, 0, 0}, {0, 1, 0}, {1, 1, 0}, {1, 0, 0}
        }}},
        // EAST (+X)
        { BlockFace::East, {1, 0, 0}, {{
            {1, 0, 0}, {0, 1, 0}, {1, 1, 0}, {1, 0, 1}
        }}},
        //WEST (-X)
        { BlockFace::West, {-1, 0, 0}, {{
            {0, 0, 1}, {0, 1, 1}, {0, 1, 0}, {0, 0, 0}
        }}}
    }};
} //namespace

Chunk::Chunk(glm::ivec3 position) 
    : m_position(position)
    , m_blocks(SIZE_X * SIZE_Y * SIZE_Z, Block{BlockType::Air})
{
}

int Chunk::index(int x, int y, int z) const {
    return x + SIZE_X * (y + SIZE_Y * z);
}

bool Chunk::isInBounds(int x, int y, int z) const {
    return  x >= 0 && x < SIZE_X && 
            y >= 0 && y < SIZE_Y &&
            z >= 0 && z < SIZE_Z;
}

Block Chunk::getBlock(int x, int y, int z) const {
    if (!isInBounds(x, y, z)) return Block{BlockType::Air};
    return m_blocks[index(x, y, z)];
}

void Chunk::setBlock(int x, int y, int z, BlockType type){
    if (!isInBounds(x, y, z)) return;
    m_blocks[index(x, y, z)].type = type;
    m_dirty = true;
}

bool Chunk::isFaceVisible(int x, int y, int z) const {
    if (!isInBounds(x, y, z)) return true;
    Block neighbor = m_blocks[index(x, y, z)];
    const BlockProperties& props = BlockRegistry::get(neighbor.type);
    return props.isTransparent;
}

glm::vec3 Chunk::getWorldPosition() const {
    return glm::vec3(m_position.x * SIZE_X, m_position.y * SIZE_Y, m_position.z * SIZE_Z);
}

void Chunk::generateMesh() {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    for (int x = 0; x < SIZE_X; ++x){
        for (int y = 0; y < SIZE_Y; ++y){
            for (int z = 0; z < SIZE_Z; ++z){
                Block block = getBlock(x, y, z);
                if (block.isAir()) continue;

                const BlockProperties& props = BlockRegistry::get(block.type);

                for (const FaceDef& face : FACES){
                    int nx = x + face.normal.x;
                    int ny = y + face.normal.y;
                    int nz = z + face.normal.z;

                    if (!isFaceVisible(nx, ny, nz)) continue;

                    float shade = 1.0f;
                    if(face.face == BlockFace::Bottom) shade = 0.5f;
                    else if (face.face == BlockFace::North || face.face == BlockFace::South) shade = 0.8f;
                    else if (face.face == BlockFace::East || face.face == BlockFace::West) shade = 0.7;

                    glm::vec3 color = props.debugColor * shade;

                    uint32_t baseIndex = (uint32_t)vertices.size();

                    for (const glm::vec3& offset : face.vertices) {
                        Vertex v;
                        v.position = glm::vec3(x, y, z) + offset;
                        v.color = color;
                        vertices.push_back(v);
                    }

                    indices.push_back(baseIndex + 0);
                    indices.push_back(baseIndex + 1);
                    indices.push_back(baseIndex + 2);
                    indices.push_back(baseIndex + 2);
                    indices.push_back(baseIndex + 3);
                    indices.push_back(baseIndex + 0);
                }
            }
        }
    }

    m_mesh = vertices.empty() ? nullptr : std::make_unique<Mesh>(vertices, indices);
    m_dirty = false;
}

void Chunk::draw(Shader& shader) const {
    if (!m_mesh) return;

    glm::mat4 model = glm::translate(glm::mat4(1.0f), getWorldPosition());
    shader.setMat4("uModel", model);

    m_mesh->draw();
}