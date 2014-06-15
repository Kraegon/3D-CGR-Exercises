#include <string>
#ifndef texture_loader_h
#define texture_loader_h
class texture_loader
{
private:
    int width, height, bpp, a;
    unsigned int textureId;
    std::string texturePath;

public:
    texture_loader(std::string);
    texture_loader();
    void getTexture(double, double);
    void initTexture(void);
    void stashTexture(void);
};
#endif