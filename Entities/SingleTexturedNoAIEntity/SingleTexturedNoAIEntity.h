#pragma once

#include "../../Texture/Texture.h"

#include <glew.h>
#include <glm.hpp>
#include <SOIL2.h>

#include <string>

class SingleTexturedNoAIEntity
{
private:

	double x;
	double y;

	double z;

	double width;
	double height;

	Texture texture;

public:

	SingleTexturedNoAIEntity(double x, double y, double z, double width, double height, std::string textureAdress);

	double GetX();
	double GetY();
	double GetZ();

	void SetX(double x);
	void SetY(double y);
	void SetZ(double z);

	double GetWidth();
	double GetHeight();

	~SingleTexturedNoAIEntity();

	int GetTextureID();

	int GetTextureWidth();
	int GetTextureHeight();
};