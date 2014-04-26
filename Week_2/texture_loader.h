#include <string>
class texture_loader
{
private:
	int a;
    std::string texturePath;

public:
	texture_loader(int a);
    texture_loader(std::string fileName);
    

	int texMethodExample(int a, int b);
    
};
