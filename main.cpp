#include <cassert>
#include <iostream>
#include <tuple>
#include "include/shader_loader.h"
#include "include/vertex_layout.h"
#include "include/texture_loader.h"
#include "GLFW/glfw3.h"

ShaderLoader * shaderLoader;
VertexLayout * vertexLayout;
TextureLoader * textureLoader;
std::vector<Vertex> vertices;
std::vector<unsigned int> indices;

std::tuple<std::vector<Vertex>, std::vector<unsigned int>> createRectangle(int rowCount, int colCount) {
    // create rectangle
    std::vector<Vertex> outVertices;
    std::vector<unsigned int> outIndices;
    float dx = 1 / float(rowCount - 1);
    float dy = 1 / float(colCount - 1);
    for (unsigned int i = 0; i != rowCount; ++i) {
        for (unsigned int j = 0; j != colCount; ++j) {
            // create current vertex.
            Vertex v;
            v.x = (dx * i) * 2 - 1;
            v.y = (dy * j) * 2 - 1;
            v.z = 0;
            v.u = dx * i;
            v.v = 1 - dy * j;
            outVertices.push_back(v);
            if (i == 0 || j == 0) continue;
            // create two triangles.
            unsigned int curIndex = i * rowCount + j;
            unsigned int leftIndex = curIndex - 1;
            unsigned int downIndex = curIndex - rowCount;
            unsigned int leftDownIndex = downIndex - 1;
            outIndices.insert(outIndices.end(), {leftIndex, downIndex, curIndex});
            outIndices.insert(outIndices.end(), {leftIndex, leftDownIndex, downIndex});
        }
    }
    return std::make_tuple(outVertices, outIndices);
}

void init() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shaderLoader = new ShaderLoader();
    vertexLayout = new VertexLayout();
    textureLoader = new TextureLoader();
    shaderLoader->loadVertexShader("./shader/vertex_shader.glsl");
    shaderLoader->loadFragmentShader("./shader/fragment_shader.glsl");
    shaderLoader->compileShaderProgram();
    RGBAFlatTexture texture1Info = textureLoader->loadRGBATexture("./resource/pic1.png");
    RGBAFlatTexture texture2Info = textureLoader->loadRGBATexture("./resource/pic2.png");
    shaderLoader->useShaderProgram();
    textureLoader->bindTexture(texture1Info, 0);
    textureLoader->bindTexture(texture2Info, 1);
    shaderLoader->setUniform("displacement_img", 0);
    shaderLoader->setUniform("img", 1);
    shaderLoader->setUniform("displacement_img_width", texture1Info.width);
    shaderLoader->setUniform("displacement_img_height", texture1Info.height);
    std::tie(vertices, indices) = createRectangle(200, 200);
    vertexLayout->passVerticesData(vertices, indices);
}

void draw() {
    static int max_pixel_offset = 10;
    static int step = 1;
    // clear pixel buffer first.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // load layout (vao).
    unsigned int vao = vertexLayout->getVAO();
    glBindVertexArray(vao);
    // draw it.
    if (max_pixel_offset > 25) step = -1;
    if (max_pixel_offset < -25) step = 1;
    shaderLoader->setUniform("max_pixel_offset", max_pixel_offset);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    max_pixel_offset += step;
    std::cout<<max_pixel_offset<<std::endl;
    _sleep(30);
}

int main() {
    // glfw: Initialize.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfw: create window.
    GLFWwindow * window = glfwCreateWindow(1200, 600, "ImageProcesser", NULL, NULL);
    assert(window != NULL);
    glfwMakeContextCurrent(window);
    // glad: load all OpenGL function pointers
    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
    // render loop
    init();
    while (!glfwWindowShouldClose(window))
    {
        draw();
        // glfw: swap buffers and poll IO events (keyspressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFWresources.
    glfwTerminate();
    return 0;
}
