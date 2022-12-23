#pragma once

#include "../../Window/Window.h"
#include "../../Entities/SingleTexturedNoAIEntity/SingleTexturedNoAIEntity.h"
#include "../SpaceRenderer/SpaceRenderer.h"
#include "../../Player/Player.h"
#include "../../Constants/Constants.h"

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <SOIL2.h>

#include <fstream>
#include <string>
#include <vector>

class EntityRenderer
{
private:

	int programID;

	int vertexShaderID;
	int fragmentShaderID;

	std::string vertexShaderCode;
	std::string fragmentShaderCode;

	std::vector<double> entity;

	unsigned int entityVAOID;
	unsigned int entityVBOID;

	int orthoPath;
	glm::mat4 ortho;

	int texturePath;

public:

	EntityRenderer(std::string vertexShaderAdress, std::string fragmentShaderAdress, Window* window);

	void StartUsing();
	void StopUsing();

	void Render(SingleTexturedNoAIEntity* entity, Window* window, SpaceRenderer* spaceRenderer, Player* player);

	~EntityRenderer();
};