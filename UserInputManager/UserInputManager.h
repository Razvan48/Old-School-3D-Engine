#pragma once

#include "../Window/Window.h"

#include "../Player/Player.h"

#include "../Map/Map.h"

class UserInputManager
{
private:

public:

	UserInputManager();

	~UserInputManager();

	void UserInput(Window* window, Player* player, Map* map);

};