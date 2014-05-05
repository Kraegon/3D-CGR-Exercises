#include <string>
class texture_loader
{
private:
    int width, height, bpp, a;
    int textureId;
    std::string texturePath;

public:
    texture_loader(const char*);
    void getTexture(double, double);
    void initTexture(void);
    void stashTexture(void);
};
