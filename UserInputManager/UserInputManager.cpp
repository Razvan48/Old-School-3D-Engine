#include "UserInputManager.h"

UserInputManager::UserInputManager()
{

}

UserInputManager::~UserInputManager()
{

}

void UserInputManager::UserInput(Window* window, Player* player, Map* map)
{
    if (glfwGetKey(window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        window->SetWindowShouldClose(true);
        return;
    }

    if (glfwGetKey(window->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        if (glfwGetKey(window->GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            double newX = player->GetX() + player->GetRunningTransSpeed() * cos(player->GetViewAngle()) * window->GetDeltaTime();
            double newY = player->GetY() + player->GetRunningTransSpeed() * sin(player->GetViewAngle()) * window->GetDeltaTime();

            if (map->GetWallID((int)newX, (int)player->GetY()) == 0)
            {
                player->SetX(newX);
            }
            if (map->GetWallID((int)player->GetX(), (int)newY) == 0)
            {
                player->SetY(newY);
            }
        }
        else
        {
            double newX = player->GetX() + player->GetTransSpeed() * cos(player->GetViewAngle()) * window->GetDeltaTime();
            double newY = player->GetY() + player->GetTransSpeed() * sin(player->GetViewAngle()) * window->GetDeltaTime();

            if (map->GetWallID((int)newX, (int)player->GetY()) == 0)
            {
                player->SetX(newX);
            }
            if (map->GetWallID((int)player->GetX(), (int)newY) == 0)
            {
                player->SetY(newY);
            }
        }
    }
    if (glfwGetKey(window->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        double newX = player->GetX() - player->GetTransSpeed() * cos(player->GetViewAngle()) * window->GetDeltaTime();
        double newY = player->GetY() - player->GetTransSpeed() * sin(player->GetViewAngle()) * window->GetDeltaTime();

        if (map->GetWallID((int)newX, (int)player->GetY()) == 0)
        {
            player->SetX(newX);
        }
        if (map->GetWallID((int)player->GetX(), (int)newY) == 0)
        {
            player->SetY(newY);
        }
    }
    if (glfwGetKey(window->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        double newX = player->GetX() - player->GetTransSpeed() * sin(player->GetViewAngle()) * window->GetDeltaTime();
        double newY = player->GetY() + player->GetTransSpeed() * cos(player->GetViewAngle()) * window->GetDeltaTime();

        if (map->GetWallID((int)newX, (int)player->GetY()) == 0)
        {
            player->SetX(newX);
        }
        if (map->GetWallID((int)player->GetX(), (int)newY) == 0)
        {
            player->SetY(newY);
        }
    }
    if (glfwGetKey(window->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        double newX = player->GetX() + player->GetTransSpeed() * sin(player->GetViewAngle()) * window->GetDeltaTime();
        double newY = player->GetY() - player->GetTransSpeed() * cos(player->GetViewAngle()) * window->GetDeltaTime();

        if (map->GetWallID((int)newX, (int)player->GetY()) == 0)
        {
            player->SetX(newX);
        }
        if (map->GetWallID((int)player->GetX(), (int)newY) == 0)
        {
            player->SetY(newY);
        }
    }

    if (map->GetWallID((int)player->GetX() + 1, (int)player->GetY()) != 0 && (int)player->GetX() * 1.0 + 1.0 - player->GetX() < player->GetBodyRadius())
    {
        player->SetX((int)player->GetX() * 1.0 + 1.0 - player->GetBodyRadius());
    }
    else if (map->GetWallID((int)player->GetX() - 1, (int)player->GetY()) != 0 && player->GetX() - (int)player->GetX() * 1.0 < player->GetBodyRadius())
    {
        player->SetX((int)player->GetX() * 1.0 + player->GetBodyRadius());
    }

    if (map->GetWallID((int)player->GetX(), (int)player->GetY() + 1) != 0 && (int)player->GetY() * 1.0 + 1.0 - player->GetY() < player->GetBodyRadius())
    {
        player->SetY((int)player->GetY() * 1.0 + 1.0 - player->GetBodyRadius());
    }
    else if (map->GetWallID((int)player->GetX(), (int)player->GetY() - 1) != 0 && player->GetY() - (int)player->GetY() * 1.0 < player->GetBodyRadius())
    {
        player->SetY((int)player->GetY() * 1.0 + player->GetBodyRadius());
    }

    double newCursorX;
    double newCursorY;

    glfwGetCursorPos(window->GetWindow(), &newCursorX, &newCursorY);

    double deltaCursorX = newCursorX - player->GetCursorX();

    if (deltaCursorX != 0.0)
    {
        player->Rotate(-deltaCursorX * player->GetRotSpeed() * window->GetDeltaTime());
        player->SetCursorX(newCursorX);
    }
}