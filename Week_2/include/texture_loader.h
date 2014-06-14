#include <string>

class texture_loader
{
private:
    int width, height, bpp, a;
    GLuint textureId;
    std::string texturePath;

public:
    texture_loader(const char*);
    texture_loader();
    void getTexture(double, double);
    void initTexture(void);
    void stashTexture(void);
};
