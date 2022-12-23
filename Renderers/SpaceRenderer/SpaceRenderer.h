#pragma once

#include "../../Window/Window.h"
#include "../../Player/Player.h"
#include "../../Map/Map.h"

#include "../../Constants/Constants.h"

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <SOIL2.h>

#include <fstream>
#include <string>
#include <vector>
#include <climits>

class SpaceRenderer
{
private:

	int programID;

	int vertexShaderID;
	int fragmentShaderID;

	std::string vertexShaderCode;
	std::string fragmentShaderCode;

	std::vector<double> floor;
	std::vector<double> ceiling;
	std::vector<double> walls;

	unsigned int floorVAOID;
	unsigned int floorVBOID;

	unsigned int ceilingVAOID;
	unsigned int ceilingVBOID;

	unsigned int wallsVAOID;
	unsigned int wallsVBOID;

	int orthoPath;
	glm::mat4 ortho;

	int texturePath;
	
	double depthBuffer[1 + MAX_SCREEN_WIDTH];

public:

	SpaceRenderer(std::string vertexShaderAdress, std::string fragmentShaderAdress, Window* window);

	void StartUsing();
	void StopUsing();

	void RenderFloor(Window* window, Player* player, Map* map);
	void RenderCeiling(Window* window, Player* player, Map* map);
	void RenderWalls(Window* window, Player* player, Map* map);

	double GetDepth(int column);
	void SetDepth(int column, double depth);

	~SpaceRenderer();

};