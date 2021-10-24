#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG

#include "../include/stb_image.h"
#include "../include/texture_loader.h"
#include "glad/glad.h"
#include <iostream>

RGBAFlatTexture TextureLoader::loadRGBATexture(const std::string & fileName) {
    RGBAFlatTexture textureInfo;
    int nrChannels;
    unsigned char * data = stbi_load(fileName.c_str(), &textureInfo.width, &textureInfo.height, &nrChannels, 0);
    if (data == nullptr) {
        std::cout << "[ERROR] Failed to load texture: " << fileName << std::endl;
        return RGBAFlatTexture({-1, -1, nullptr});
    }
    if (nrChannels == 4) textureInfo.pixels = reinterpret_cast<RGBAFlatTexture::Pixel *>(data);
    else if(nrChannels == 3) {
        textureInfo.pixels = new RGBAFlatTexture::Pixel[textureInfo.width * textureInfo.height];
        for (auto i = 0; i != textureInfo.width * textureInfo.height; ++i) {
            memcpy(textureInfo.pixels + i, data + i * 3, 3);
            textureInfo.pixels[i].a = 255;
        }
    }
    return textureInfo;
}

unsigned int TextureLoader::bindTexture(RGBAFlatTexture textureInfo, int textureUniformPlace) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0 + textureUniformPlace);
    glBindTexture(GL_TEXTURE_2D, texture);
    // setting texture display approach.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureInfo.width, textureInfo.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char *)textureInfo.pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    return texture;
}
