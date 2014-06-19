#include "../include/ObjModel.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include "glut.h" //Requires adding glut.h to solution
#include <functional>
#include <locale>  
#elif  __gnu_linux__
#include <GL/glut.h>
#else
#error "Your OS cannot compile this program!"
#endif
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>


std::string replace(std::string str, std::string toReplace, std::string replacement)
{
	size_t index = 0;
	while (true) 
	{
		 index = str.find(toReplace, index);
		 if (index == std::string::npos) 
			 break;
		 str.replace(index, toReplace.length(), replacement);
		 ++index;
	}
	return str;
}

std::vector<std::string> split(std::string str, std::string sep)
{
	std::vector<std::string> ret;
	size_t index;
	while(true)
	{
		index = str.find(sep);
		if(index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index+1);
	}
	ret.push_back(str);
	return ret;
}

inline std::string toLower(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

// Extensions for std::string to trim whitespace
string& trimR(string& str)
{
	if (!str.size()) return str;
	// find the last whitespace chr, then delete from there to end.
	string::iterator iter = --str.end();
	while (isspace(*iter)) --iter;
	str.erase(++iter, str.end());
	return str;
}
string& trimL(string& str)
{
	if (!str.size()) return str;
	// find first non-whitespace, then delete from begin to there.
	string::iterator iter = str.begin();
	while (iter != str.end() && isspace(*iter)) ++iter;
	str.erase(str.begin(), iter);
	return str;
}
string& trim(string& str)
{
	return trimR(trimL(str));
}


ObjModel::ObjModel(std::string fileName)
{
	std::string dirName = fileName;
	if(dirName.rfind("/") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("/"));
	if(dirName.rfind("\\") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("\\"));
	if(fileName == dirName)
		dirName = "";


	std::ifstream pFile(fileName.c_str());

	if(!pFile){
		std::cout<<"Obj not loaded"<<std::endl;
		std::exit(0);
	}

	ObjGroup* currentGroup = new ObjGroup();
	currentGroup->materialIndex = -1;


	while(!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);

		line = replace(line, "\t", " ");
		while(line.find("  ") != std::string::npos)
			line = replace(line, "  ", " ");
		if(line == "")
			continue;
		if(line[0] == ' ')
			line = line.substr(1);
		if(line == "")
			continue;
		if(line[line.length()-1] == ' ')
			line = line.substr(0, line.length()-1);
		if(line == "")
			continue;
		if(line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if(params[0] == "v")
			vertices.push_back(Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if(params[0] == "vn")
			normals.push_back(Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if(params[0] == "vt")
			texcoords.push_back(Vec2f((float)atof(params[1].c_str()), (float)atof(params[2].c_str())));
		else if(params[0] == "f")
		{
			for(size_t ii = 4; ii <= params.size(); ii++)
			{
				Face face;

				for(size_t i = ii-3; i < ii; i++)	//magische forlus om van quads triangles te maken ;)
				{
					Vertex vertex;
					std::vector<std::string> indices = split(params[i == (ii-3) ? 1 : i], "/");
					if (indices.size() >= 1)	//er is een positie
						vertex.position = atoi(indices[0].c_str()) - 1;
					if(indices.size() == 2)		//alleen texture
						vertex.texcoord = atoi(indices[1].c_str())-1;
					if(indices.size() == 3)		//v/t/n of t//n
					{
						if( indices[1] != "")
							vertex.texcoord = atoi(indices[1].c_str())-1;
						vertex.normal = atoi(indices[2].c_str())-1;
					}
					face.vertices.push_back(vertex);
				}
				currentGroup->faces.push_back(face);
			}
		}
		else if(params[0] == "s")
		{//smoothing
		}
        else if(params[0] == "mtllib")
        {
            loadMaterialFile(dirName + "/" + params[1], dirName);
        }
		else if(params[0] == "usemtl")
		{
			if(currentGroup->faces.size() != 0)
				groups.push_back(currentGroup);
			currentGroup = new ObjGroup();
			currentGroup->materialIndex = -1;

			for(size_t i = 0; i < materials.size(); i++)
			{
				MaterialInfo* info = materials[i];
				if(info->name == params[1])
				{
					currentGroup->materialIndex = i;
					break;
				}
			}
			if(currentGroup->materialIndex == -1)
				std::cout<<"Could not find material name "<<params[1]<<std::endl;
		}
	}
	groups.push_back(currentGroup);
}


ObjModel::~ObjModel(void)
{
}




void ObjModel::draw()
{
	for(ObjGroup *group: groups){
		//Set material, probably glMaterial or something
		if(materials[group->materialIndex]->hasTexture){
			materials[group->materialIndex]->texture.initTexture();
		}
		glBegin(GL_TRIANGLES);
		for(Face f : group->faces){
			for(std::list<Vertex>::iterator it = f.vertices.begin(); it != f.vertices.end(); ++it){
				glNormal3f(normals[it->normal].x, normals[it->normal].y, normals[it->normal].z);
				glTexCoord2f(texcoords[it->texcoord].x, texcoords[it->texcoord].y);
				glVertex3f(vertices[it->position].x, vertices[it->position].y, vertices[it->position].z);
			}
		}
		glEnd();
		if(materials[group->materialIndex]->hasTexture){
			materials[group->materialIndex]->texture.stashTexture();
		}
	}
}

void ObjModel::scaleModel(double factor)
{
	for(std::vector<Vec3f>::iterator it = vertices.begin(); it != vertices.end(); ++it){
		it->x*=(1/factor);
		it->y*=(1/factor);
		it->z*=(1/factor);
	}
}

void ObjModel::loadMaterialFile( std::string fileName, std::string dirName )
{
	trim(fileName);
	std::ifstream pFile(fileName.c_str());
	if(!pFile){
		std::cout<<"Mat not loaded"<<std::endl;
		std::exit(0);
	}

	MaterialInfo* currentMaterial = NULL;

	while(!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		line = replace(line, "\t", " ");
		while(line.find("  ") != std::string::npos)
			line = replace(line, "  ", " ");
		if(line == "")
			continue;
		if(line[0] == ' ')
			line = line.substr(1);
		if(line == "")
			continue;
		if(line[line.length()-1] == ' ')
			line = line.substr(0, line.length()-1);
		if(line == "")
			continue;
		if(line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if(params[0] == "newmtl")
		{
			if(currentMaterial != NULL)
			{
				materials.push_back(currentMaterial);
			}
			currentMaterial = new MaterialInfo();
			currentMaterial->name = params[1];
		}
		else if(params[0] == "map_kd")
		{
			currentMaterial->hasTexture = true;
			std::string texPath = dirName + "/" + params[1];
			texPath = replace(texPath, "\\", "/");
			trimR(texPath);
			currentMaterial->texture = texture_loader(texPath);
		}
		else
			std::cout<<"Didn't parse "<<params[0]<<" in material file"<<std::endl;
	}
	if(currentMaterial != NULL)
		materials.push_back(currentMaterial);

}

ObjModel::MaterialInfo::MaterialInfo()
{
	hasTexture = false;
}


Vec3f::Vec3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vec3f::Vec3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vec3f::Vec3f(const Vec3f &other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float& Vec3f::operator [](int index)
{
	return v[index];
}



Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vec2f::Vec2f()
{
	this->x = 0;
	this->y = 0;
}
Vec2f::Vec2f(const Vec2f &other)
{
	this->x = other.x;
	this->y = other.y;
}

float& Vec2f::operator [](int index)
{
	return v[index];
}
