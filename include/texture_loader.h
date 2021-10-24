#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <string>

struct RGBAFlatTexture {
    int height = 0;
    int width = 0;
    struct Pixel {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    } * pixels;
};

class TextureLoader {
public:
    RGBAFlatTexture loadRGBATexture(const std::string & fileName);
    unsigned int bindTexture(RGBAFlatTexture textureInfo, int textureUniformPlace);
};

#endif
