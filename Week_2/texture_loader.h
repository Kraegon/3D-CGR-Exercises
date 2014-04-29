#include <string>
class texture_loader
{
private:
    int width, height, bpp, a;
    GLuint textureId;
    std::string texturePath;

public:
    texture_loader(const char*);
    void getTexture(int, int);
    void initTexture(void);
};
