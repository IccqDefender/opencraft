#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>
#include "Vertex.h"

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    void draw() const;
private:
    void setupMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    void release();

    GLuint m_VAO = 0, m_VBO = 0, m_EBO = 0;
    GLsizei m_indexCount = 0;
};

#endif // MESH_H