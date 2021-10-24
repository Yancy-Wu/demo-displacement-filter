#include "../include/shader_loader.h"
#include <fstream>
#include <iostream>
#include <sstream>

const char * loadFileContent(const std::string & fileName) {
    std::ifstream file_stream;
    file_stream.open(fileName, std::ios::in);
    file_stream.seekg(0, std::ios::end);
    unsigned int length = file_stream.tellg();
    char * buffer = new char[length + 1];
    memset(buffer, 0, length + 1);
    file_stream.seekg(0, std::ios::beg);
    file_stream.read(buffer, length);
    file_stream.close();
    return buffer;
}

unsigned int ShaderLoader::_compileShader(unsigned int shaderType, const std::string & fileName) {
    // create vertex shader.
    unsigned int shader = 0;
    shader = glCreateShader(shaderType);
    // compile source code.
    const char * shaderSourceCodePointer = loadFileContent(fileName);
    glShaderSource(shader, 1, &shaderSourceCodePointer, NULL);
    glCompileShader(shader);
    // check success or not.
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "[ERROR] SHADER::COMPILATION_FAILED: "<< fileName << "\n" << infoLog << std::endl;
    }
    return shader;
}

void ShaderLoader::loadVertexShader(const std::string & fileName) {
    this->_vertexShader = this->_compileShader(GL_VERTEX_SHADER, fileName);
}

void ShaderLoader::loadFragmentShader(const std::string & fileName) {
    this->_fragmentShader = this->_compileShader(GL_FRAGMENT_SHADER, fileName);
}

void ShaderLoader::compileShaderProgram() {
     // create shader program (a batch of shader).
    unsigned int shaderProgram = 0;
    shaderProgram = glCreateProgram();
    // link my shaders.
    glAttachShader(shaderProgram, this->_vertexShader);
    glAttachShader(shaderProgram, this->_fragmentShader);
    glLinkProgram(shaderProgram);
    // check success.
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "[ERROR] SHADER::LINK_PROGRAM_FAILED:\n" << infoLog << std::endl;
    }
    this->_shaderProgram = shaderProgram;
};
