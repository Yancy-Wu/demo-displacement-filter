#ifndef SHADER_COMPILER_H
#define SHADER_COMPILER_H

#include <string>
#include <glad/glad.h>

class ShaderLoader {
private:
    unsigned int _shaderProgram = -1;
    unsigned int _vertexShader = -1;
    unsigned int _fragmentShader = -1;
    unsigned int _compileShader(unsigned int shaderType, const std::string & fileName);
public:
    void loadVertexShader(const std::string & fileName);
    void loadFragmentShader(const std::string & fileName);
    void compileShaderProgram();
    void useShaderProgram() { glUseProgram(this->_shaderProgram); }
    void setUniform(const std::string & varName, int value) { glUniform1i(glGetUniformLocation(this->_shaderProgram, varName.c_str()), value); }
};

#endif
