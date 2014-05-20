#ifdef _WIN32
#include <stdlib.h>
#include <windows.h>
#else
#include <unistd.h> //Test compatibility of unistd.h's sleep with Apple systems
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <glut.h>
#elif  __gnu_linux__
#include <GL/glut.h>
#else
#error "Your OS cannot compile this program!"
#endif
#include "../include/texture_loader.h"
#include <string>
#include "stb_image.c"
using namespace std;


texture_loader::texture_loader(const char* fileName)
{
    texturePath = string(fileName);
}

void texture_loader::initTexture(void)
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    unsigned char* imgData = stbi_load(texturePath.c_str(), &width, &height, &bpp, 4);
    glTexImage2D(	GL_TEXTURE_2D,
                 0,		//level
                 GL_RGBA,		//internal format
                 width,		//width
                 height,		//height
                 0,		//border
                 GL_RGBA,		//data format
                 GL_UNSIGNED_BYTE,	//data type
                 imgData);		//data
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(imgData);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glEnable(GL_TEXTURE_2D);
}

void texture_loader::getTexture(double x, double y)
{
    if (x>1||y>1||x<0||y<0) {
        printf("I can't use values above 1 or below 0!");
    }
    else glTexCoord2f(x,y);
}

void texture_loader::stashTexture(void)
{
    glDisable(GL_TEXTURE_2D);
}


