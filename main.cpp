#include "Window/Window.h"

#include "Player/Player.h"
#include "Map/Map.h"

#include "Renderers/SpaceRenderer/SpaceRenderer.h"
#include "Renderers/EntityRenderer/EntityRenderer.h"

#include "UserInputManager/UserInputManager.h"

#include "Entities/SingleTexturedNoAIEntity/SingleTexturedNoAIEntity.h"

//Pentru debug, console log.
#include <iostream>
//

int main()
{
	Window* window = new Window(756, 756, "Haunted House Escape");

	SpaceRenderer* spaceRenderer = new SpaceRenderer("Renderers/SpaceRenderer/Shaders/SpaceVertexShader.txt", "Renderers/SpaceRenderer/Shaders/SpaceFragmentShader.txt", window);
	EntityRenderer* entityRenderer = new EntityRenderer("Renderers/EntityRenderer/Shaders/EntityVertexShader.txt", "Renderers/EntityRenderer/Shaders/EntityFragmentShader.txt", window);

	Player* player = new Player(2.0, 2.0, 0.0);
	Map* map = new Map("Map/Levels/TestLevel1.txt", "Map/Textures/TestFloorTexture1.png", 2, "Map/Textures/TestWallAtlas1.png", "Map/Textures/TestCeilingTexture1.png");

	UserInputManager* userInputManager = new UserInputManager();

	SingleTexturedNoAIEntity* barrel1 = new SingleTexturedNoAIEntity(21.5, 21.5, 0.0, 0.25, 0.5, "Entities/SingleTexturedNoAIEntity/Textures/TestBarrelTexture1.png");
	SingleTexturedNoAIEntity* barrel2 = new SingleTexturedNoAIEntity(10.5, 10.5, 0.0, 0.25, 0.5, "Entities/SingleTexturedNoAIEntity/Textures/TestBarrelTexture1.png");

	while (!window->ShouldWindowClose())
	{
		window->PreFrameDraw();

		spaceRenderer->StartUsing();
		spaceRenderer->RenderFloor(window, player, map);
		spaceRenderer->RenderCeiling(window, player, map);
		spaceRenderer->RenderWalls(window, player, map);

		entityRenderer->StartUsing();
		entityRenderer->Render(barrel1, window, spaceRenderer, player);
		entityRenderer->Render(barrel2, window, spaceRenderer, player);

		userInputManager->UserInput(window, player, map);

		window->PostFrameDraw();

		std::cout << "FPS: " << window->ShowFPS() << '\n';
		//std::cout << "X: " << player->GetX() << '\n';
		//std::cout << "Y: " << player->GetY() << '\n';
		//std::cout << "Angle: " << player->GetViewAngle() << '\n';
	}

	delete barrel1;
	delete barrel2;

	delete userInputManager;

	delete map;
	delete player;

	delete entityRenderer;
	delete spaceRenderer;

	delete window;

	return 0;
}

