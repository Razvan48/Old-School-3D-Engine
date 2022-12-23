#include "Map.h"

Map::Map(std::string levelMapAdress, std::string floorTextureAdress, int numberOfWalls, std::string wallAtlasAdress, std::string ceilingTextureAdress)
{
	std::ifstream FIN(levelMapAdress);

	FIN >> this->width;
	FIN >> this->height;

	for (int y = this->height - 1; y >= 0; y--)
	{
		for (int x = 0; x < this->width; x++)
		{
			FIN >> this->wall[x][y];
		}
	}

	glGenTextures(1, &this->floorTexture.ID);
	glBindTexture(GL_TEXTURE_2D, this->floorTexture.ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char* dataFloor = SOIL_load_image(floorTextureAdress.c_str(), &this->floorTexture.width, &this->floorTexture.height, &this->floorTexture.nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->floorTexture.width, this->floorTexture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataFloor);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(dataFloor);

	this->numberOfWalls = numberOfWalls;

	glGenTextures(1, &this->wallAtlas.ID);
	glBindTexture(GL_TEXTURE_2D, this->wallAtlas.ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char* dataWall = SOIL_load_image(wallAtlasAdress.c_str(), &this->wallAtlas.width, &this->wallAtlas.height, &this->wallAtlas.nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->wallAtlas.width, this->wallAtlas.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataWall);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(dataWall);

	glGenTextures(1, &this->ceilingTexture.ID);
	glBindTexture(GL_TEXTURE_2D, this->ceilingTexture.ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char* dataCeiling = SOIL_load_image(ceilingTextureAdress.c_str(), &this->ceilingTexture.width, &this->ceilingTexture.height, &this->ceilingTexture.nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->ceilingTexture.width, this->ceilingTexture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataCeiling);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(dataCeiling);
}

Map::~Map()
{

}

int Map::GetWallID(int x, int y)
{
	if (0 <= x && x < this->width && 0 <= y && y < this->height)
	{
		return this->wall[x][y];
	}
	
	return INT_MIN;
}

int Map::GetHeight()
{
	return this->height;
}

int Map::GetWidth()
{
	return this->width;
}

int Map::GetFloorTextureID()
{
	return this->floorTexture.ID;
}

int Map::GetNumberOfWalls()
{
	return this->numberOfWalls;
}

int Map::GetWallAtlasID()
{
	return this->wallAtlas.ID;
}

int Map::GetCeilingTextureID()
{
	return this->ceilingTexture.ID;
}

double Map::GetCeilingLevel()
{
	return this->ceilingLevel;
}
