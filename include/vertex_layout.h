#ifndef VERTEX_H
#define VERTEX_H

#include <glad/glad.h>
#include <vector>

struct Vertex {
    float x, y, z;
    float u, v;
};

class VertexLayout {
private:
    unsigned int vertexBuffer = -1;
    unsigned int indexBuffer = -1;
    unsigned int vao = -1;
public:
    VertexLayout() {
        // create vao and vertex buffer.
        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);
        glGenBuffers(1, &this->indexBuffer);
        glGenBuffers(1, &this->vertexBuffer);
    }
    unsigned int getVAO() {
        return this->vao;
    }
    void passVerticesData(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices) {
        // care: you cannot modify vertex array buffer after enable vertex attr array.
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3* sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }
};

#endif
