#include "SingleTexturedNoAIEntity.h"

SingleTexturedNoAIEntity::SingleTexturedNoAIEntity(double x, double y, double z, double width, double height, std::string textureAdress)
{
	this->x = x;
	this->y = y;

	this->z = z;

	this->width = width;
	this->height = height;

	glGenTextures(1, &this->texture.ID);
	glBindTexture(GL_TEXTURE_2D, this->texture.ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char* data = SOIL_load_image(textureAdress.c_str(), &this->texture.width, &this->texture.height, &this->texture.nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->texture.width, this->texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(data);
}

SingleTexturedNoAIEntity::~SingleTexturedNoAIEntity()
{

}

double SingleTexturedNoAIEntity::GetX()
{
	return this->x;
}

double SingleTexturedNoAIEntity::GetY()
{
	return this->y;
}

double SingleTexturedNoAIEntity::GetZ()
{
	return this->z;
}

void SingleTexturedNoAIEntity::SetX(double x)
{
	this->x = x;
}

void SingleTexturedNoAIEntity::SetY(double y)
{
	this->y = y;
}

void SingleTexturedNoAIEntity::SetZ(double z)
{
	this->z = z;
}

double SingleTexturedNoAIEntity::GetWidth()
{
	return this->width;
}

double SingleTexturedNoAIEntity::GetHeight()
{
	return this->height;
}

int SingleTexturedNoAIEntity::GetTextureID()
{
	return this->texture.ID;
}

int SingleTexturedNoAIEntity::GetTextureWidth()
{
	return this->texture.width;
}

int SingleTexturedNoAIEntity::GetTextureHeight()
{
	return this->texture.height;
}