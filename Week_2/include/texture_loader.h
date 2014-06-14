#ifndef TEXTURE_LOADER_H_
#define TEXTURE_LOADER_H_
#include <string>

class texture_loader
{
private:
    int width, height, bpp, a;
    unsigned int textureId;
    std::string texturePath;

public:
    texture_loader(const char*);
    texture_loader();
    void getTexture(double, double);
    void initTexture(void);
    void stashTexture(void);
};

#endif
