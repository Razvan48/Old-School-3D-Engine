#pragma once

#include "../Constants/Constants.h"
#include "../Texture/Texture.h"

#include <glew.h>
#include <glm.hpp>
#include <SOIL2.h>

#include <fstream>
#include <vector>
#include <string>

#include <climits>

class Map
{
private:

	int width;
	int height;

	int wall[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];

	Texture floorTexture;

	int numberOfWalls;
	Texture wallAtlas;

	Texture ceilingTexture;

	double ceilingLevel = 1.0;

public:

	Map(std::string levelMapAdress, std::string floorTextureAdress, int numberOfWalls, std::string wallAtlasAdress, std::string ceilingTextureAdress);

	~Map();

	int GetWallID(int x, int y);

	int GetHeight();
	int GetWidth();

	int GetFloorTextureID();

	int GetNumberOfWalls();
	int GetWallAtlasID();

	int GetCeilingTextureID();

	double GetCeilingLevel();
};

