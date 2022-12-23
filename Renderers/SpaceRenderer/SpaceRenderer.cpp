#include "SpaceRenderer.h"

SpaceRenderer::SpaceRenderer(std::string vertexShaderAdress, std::string fragmentShaderAdress, Window* window)
{
    this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string line;

    std::ifstream vertexFIN(vertexShaderAdress);

    while (!vertexFIN.eof())
    {
        getline(vertexFIN, line);

        this->vertexShaderCode += line;
        this->vertexShaderCode += "\n";
    }

    this->vertexShaderCode += "\0";

    vertexFIN.close();

    std::ifstream fragmentFIN(fragmentShaderAdress);

    while (!fragmentFIN.eof())
    {
        getline(fragmentFIN, line);

        this->fragmentShaderCode += line;
        this->fragmentShaderCode += "\n";
    }

    this->fragmentShaderCode += "\0";

    fragmentFIN.close();

    const char* vertexCstr = (this->vertexShaderCode).c_str();
    const char* fragmentCstr = (this->fragmentShaderCode).c_str();

    glShaderSource(this->vertexShaderID, 1, &vertexCstr, 0);
    glShaderSource(this->fragmentShaderID, 1, &fragmentCstr, 0);

    glCompileShader(this->vertexShaderID);
    glCompileShader(this->fragmentShaderID);

    this->programID = glCreateProgram();
    glAttachShader(this->programID, this->vertexShaderID);
    glAttachShader(this->programID, this->fragmentShaderID);

    glLinkProgram(this->programID);

    //glValidateProgram(this->programID);

    glUseProgram(this->programID);

    glGenVertexArrays(1, &this->floorVAOID);
    glGenBuffers(1, &this->floorVBOID);

    glGenVertexArrays(1, &this->ceilingVAOID);
    glGenBuffers(1, &this->ceilingVBOID);

    glGenVertexArrays(1, &this->wallsVAOID);
    glGenBuffers(1, &this->wallsVBOID);

    glBindVertexArray(this->floorVAOID);
    glBindBuffer(GL_ARRAY_BUFFER, this->floorVBOID);

    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)(2 * sizeof(double)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(this->ceilingVAOID);
    glBindBuffer(GL_ARRAY_BUFFER, this->ceilingVBOID);

    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)(2 * sizeof(double)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(this->wallsVAOID);
    glBindBuffer(GL_ARRAY_BUFFER, this->wallsVBOID);

    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)(2 * sizeof(double)));
    glEnableVertexAttribArray(1);

    this->ortho = glm::ortho(0.0f, (float)window->GetWidth(), 0.0f, (float)window->GetHeight());
    this->orthoPath = glGetUniformLocation(this->programID, "ortho");
    glUniformMatrix4fv(this->orthoPath, 1, GL_FALSE, glm::value_ptr(this->ortho));

    this->texturePath = glGetUniformLocation(this->programID, "texture0");
    glUniform1i(this->texturePath, 0);

    glActiveTexture(GL_TEXTURE0);

    //glUseProgram(0);
}

void SpaceRenderer::StartUsing()
{
    glUseProgram(this->programID);
}

void SpaceRenderer::StopUsing()
{
    glUseProgram(0);
}

void SpaceRenderer::RenderFloor(Window* window, Player* player, Map* map)
{
    this->floor.clear();
    glBindTexture(GL_TEXTURE_2D, map->GetFloorTextureID());

    for (int i = 0; i < window->GetHeight() / 2; i++)
    {
        double rayAngle = player->GetVerticalAngle() * (1.0 - (i * 1.0 / (window->GetHeight() * 0.5)));

        double horizontalDistToGround = player->GetZ() / tan(rayAngle);

        double leftAngle = player->GetViewAngle() + player->GetFieldOfView() / 2.0;
        double rightAngle = player->GetViewAngle() - player->GetFieldOfView() / 2.0;

        while (leftAngle >= 2.0 * PI)
        {
            leftAngle -= 2.0 * PI;
        }
        while (leftAngle < 0.0)
        {
            leftAngle += 2.0 * PI;
        }

        while (rightAngle >= 2.0 * PI)
        {
            rightAngle -= 2.0 * PI;
        }
        while (rightAngle < 0.0)
        {
            rightAngle += 2.0 * PI;
        }

        double xLeft = player->GetX() + horizontalDistToGround * cos(leftAngle);
        double yLeft = player->GetY() + horizontalDistToGround * sin(leftAngle);

        double xRight = player->GetX() + horizontalDistToGround * cos(rightAngle);
        double yRight = player->GetY() + horizontalDistToGround * sin(rightAngle);

        this->floor.push_back(0.0);
        this->floor.push_back(i * 1.0);

        //
        this->floor.push_back(xLeft / (map->GetWidth() * 1.0));//
        this->floor.push_back(1.0 - yLeft / (map->GetHeight() * 1.0));//
        //

        this->floor.push_back(window->GetWidth() * 1.0);
        this->floor.push_back(i * 1.0);

        //
        this->floor.push_back(xRight / (map->GetWidth() * 1.0));//
        this->floor.push_back(1.0 - yRight / (map->GetHeight() * 1.0));//
        //
    }

    if (floor.size())
    {
        glBindVertexArray(this->floorVAOID);
        glBindBuffer(GL_ARRAY_BUFFER, this->floorVBOID);

        glBufferData(GL_ARRAY_BUFFER, sizeof(double) * this->floor.size(), &this->floor[0], GL_DYNAMIC_DRAW);

        glDrawArrays(GL_LINES, 0, floor.size() / 4);
    }
}

void SpaceRenderer::RenderWalls(Window* window, Player* player, Map* map)
{
    this->walls.clear();
    glBindTexture(GL_TEXTURE_2D, map->GetWallAtlasID());

    for (int i = 0; i <= window->GetWidth(); i++)
    {
        double rayAngle = player->GetViewAngle() + player->GetFieldOfView() * (0.5 - i * 1.0 / window->GetWidth());

        while (rayAngle >= 2.0 * PI)
        {
            rayAngle -= 2.0 * PI;
        }
        while (rayAngle < 0.0)
        {
            rayAngle += 2.0 * PI;
        }

        int xTile = (int)player->GetX();
        int yTile = (int)player->GetY();

        double horizontalStart;
        double verticalStart;

        int xStep;
        int yStep;

        double horizontalDistance;
        double verticalDistance;

        if (0.0 < rayAngle && rayAngle < PI / 2.0) //Cadranul I
        {
            horizontalDistance = 1.0 / cos(rayAngle);
            xStep = 1;
            verticalDistance = 1.0 / sin(rayAngle);
            yStep = 1;

            horizontalStart = (xTile * 1.0 + 1.0 - player->GetX()) / cos(rayAngle);
            verticalStart = (yTile * 1.0 + 1.0 - player->GetY()) / sin(rayAngle);
        }
        else if (PI / 2.0 < rayAngle && rayAngle < PI) //Cadranul II
        {
            horizontalDistance = 1.0 / cos(PI - rayAngle);
            xStep = -1;
            verticalDistance = 1.0 / sin(PI - rayAngle);
            yStep = 1;

            horizontalStart = (player->GetX() - xTile * 1.0) / cos(PI - rayAngle);
            verticalStart = (yTile * 1.0 + 1.0 - player->GetY()) / sin(PI - rayAngle);
        }
        else if (PI < rayAngle && rayAngle < 3.0 * PI / 2.0) //Cadranul III
        {
            horizontalDistance = 1.0 / cos(rayAngle - PI);
            xStep = -1;
            verticalDistance = 1.0 / sin(rayAngle - PI);
            yStep = -1;

            horizontalStart = (player->GetX() - xTile * 1.0) / cos(rayAngle - PI);
            verticalStart = (player->GetY() - yTile * 1.0) / sin(rayAngle - PI);
        }
        else if (3.0 * PI / 2.0 < rayAngle && rayAngle < 2.0 * PI) //Cadranul IV
        {
            horizontalDistance = 1.0 / cos(2.0 * PI - rayAngle);
            xStep = 1;
            verticalDistance = 1.0 / sin(2.0 * PI - rayAngle);
            yStep = -1;

            horizontalStart = (xTile * 1.0 + 1.0 - player->GetX()) / cos(2.0 * PI - rayAngle);
            verticalStart = (player->GetY() - yTile * 1.0) / sin(2.0 * PI - rayAngle);
        }
        else if (rayAngle == 0.0)
        {
            horizontalDistance = 1.0;
            xStep = 1;
            verticalDistance = map->GetWidth() * 1.0 + map->GetHeight() * 1.0 + 1.0; //Ceva mare
            yStep = 0;

            horizontalStart = xTile * 1.0 + 1.0 - player->GetX();
            verticalStart = map->GetWidth() * 1.0 + map->GetHeight() * 1.0 + 1.0; //Ceva mare
        }
        else if (rayAngle == PI)
        {
            horizontalDistance = 1.0;
            xStep = -1;
            verticalDistance = map->GetWidth() * 1.0 + map->GetHeight() * 1.0 + 1.0; //Ceva mare
            yStep = 0;

            horizontalStart = player->GetX() - xTile * 1.0;
            verticalStart = map->GetWidth() * 1.0 + map->GetHeight() * 1.0 + 1.0; //Ceva mare
        }
        else if (rayAngle == PI / 2.0)
        {
            horizontalDistance = map->GetWidth() * 1.0 + map->GetHeight() * 1.0 + 1.0; //Ceva mare
            xStep = 0;
            verticalDistance = 1.0f;
            yStep = 1;

            horizontalStart = map->GetWidth() * 1.0 + map->GetHeight() * 1.0 + 1.0; //Ceva mare
            verticalStart = yTile * 1.0 + 1.0 - player->GetY();
        }
        else
        {
            horizontalDistance = map->GetWidth() * 1.0 + map->GetHeight() * 1.0 + 1.0; //Ceva mare
            xStep = 0;
            verticalDistance = 1.0;
            yStep = -1;

            horizontalStart = map->GetWidth() * 1.0 + map->GetHeight() * 1.0 + 1.0; //Ceva mare
            verticalStart = player->GetY() - yTile * 1.0;
        }

        bool hitHorizontalSide;

        double horizontalMadeDistance;
        double verticalMadeDistance;

        bool horizontalStartAdded = false;
        bool verticalStartAdded = false;

        if (horizontalStart < verticalStart)
        {
            horizontalMadeDistance = horizontalStart;
            hitHorizontalSide = true;
            xTile += xStep;

            horizontalStartAdded = true;
        }
        else
        {
            verticalMadeDistance = verticalStart;
            hitHorizontalSide = false;
            yTile += yStep;

            verticalStartAdded = true;
        }

        while (map->GetWallID(xTile, yTile) == 0)
        {
            if (!horizontalStartAdded)
            {
                if (horizontalStart < verticalMadeDistance + verticalDistance)
                {
                    horizontalMadeDistance = horizontalStart;
                    hitHorizontalSide = true;
                    xTile += xStep;

                    horizontalStartAdded = true;
                }
                else
                {
                    verticalMadeDistance += verticalDistance;
                    hitHorizontalSide = false;
                    yTile += yStep;
                }
            }
            else if (!verticalStartAdded)
            {
                if (horizontalMadeDistance + horizontalDistance < verticalStart)
                {
                    horizontalMadeDistance += horizontalDistance;
                    hitHorizontalSide = true;
                    xTile += xStep;
                }
                else
                {
                    verticalMadeDistance = verticalStart;
                    hitHorizontalSide = false;
                    yTile += yStep;

                    verticalStartAdded = true;
                }
            }
            else
            {
                if (hitHorizontalSide)
                {
                    if (horizontalMadeDistance + horizontalDistance < verticalMadeDistance + verticalDistance)
                    {
                        horizontalMadeDistance += horizontalDistance;

                        xTile += xStep;
                    }
                    else
                    {
                        verticalMadeDistance += verticalDistance;

                        hitHorizontalSide = false;

                        yTile += yStep;
                    }
                }
                else
                {
                    if (horizontalMadeDistance + horizontalDistance < verticalMadeDistance + verticalDistance)
                    {
                        horizontalMadeDistance += horizontalDistance;

                        hitHorizontalSide = true;

                        xTile += xStep;
                    }
                    else
                    {
                        verticalMadeDistance += verticalDistance;

                        yTile += yStep;
                    }
                }
            }
        }

        int wallID = map->GetWallID(xTile, yTile);
        if (wallID == INT_MIN || wallID > map->GetNumberOfWalls())
        {
            wallID = 1;
        }

        double distance;
        double textureCoord;

        int sideOfWallHit = 1;
        // 1 = E(hit side), 2 = N, 3 = W, 4 = S;

        if (hitHorizontalSide)
        {
            distance = horizontalMadeDistance;
            textureCoord = player->GetY() * 1.0 + distance * sin(rayAngle) - (int)(player->GetY() * 1.0 + distance * sin(rayAngle));

            if (0.0 <= rayAngle && rayAngle < PI / 2.0 || 3.0 * PI / 2.0 < rayAngle && rayAngle <= 2 * PI)
            {
                textureCoord = 1.0 - textureCoord;
                sideOfWallHit = 3;
            }
            else if (PI / 2.0 < rayAngle && rayAngle < 3.0 * PI / 2.0)
            {
                sideOfWallHit = 1;
            }
        }
        else
        {
            distance = verticalMadeDistance;
            textureCoord = player->GetX() * 1.0 + distance * cos(rayAngle) - (int)(player->GetX() * 1.0 + distance * cos(rayAngle));

            if (0.0 < rayAngle && rayAngle < PI)
            {
                sideOfWallHit = 4;
            }
            else if (PI < rayAngle && rayAngle < 2 * PI)
            {
                textureCoord = 1.0 - textureCoord;
                sideOfWallHit = 2;
            }
        }

        double angle;

        angle = player->GetViewAngle() - rayAngle;

        this->depthBuffer[i] = distance;

        distance = distance * cos(angle);

        //this->depthBuffer[i] = distance;

        double columnDimDown = (atan(player->GetZ() / distance) / player->GetVerticalAngle()) * (window->GetHeight() / 2.0);
        double columnDimUp = (atan((map->GetCeilingLevel() - player->GetZ()) / distance) / player->GetVerticalAngle()) * (window->GetHeight() / 2.0);

        this->walls.push_back(i * 1.0);
        this->walls.push_back(window->GetHeight() / 2.0 + columnDimUp);

        //In sistemul de coordonate al unei texturi, O(0,0) se afla in coltul din STANGA SUS, NU STANGA JOS.
        //
        this->walls.push_back((1.0 * wallID + textureCoord) / (map->GetNumberOfWalls() * 1.0 + 1.0));//
        this->walls.push_back((sideOfWallHit * 1.0 - 1.0) / 4.0);//
        //

        this->walls.push_back(i * 1.0);
        this->walls.push_back(window->GetHeight() / 2.0 - columnDimDown);

        //
        this->walls.push_back((1.0 * wallID + textureCoord) / (map->GetNumberOfWalls() * 1.0 + 1.0));//
        this->walls.push_back((sideOfWallHit * 1.0) / 4.0);//
        //
    }

    if (walls.size() > 0)
    {
        glBindVertexArray(this->wallsVAOID);
        glBindBuffer(GL_ARRAY_BUFFER, this->wallsVBOID);

        glBufferData(GL_ARRAY_BUFFER, sizeof(double) * this->walls.size(), &this->walls[0], GL_DYNAMIC_DRAW);

        glDrawArrays(GL_LINES, 0, walls.size() / 4);
    }
}

void SpaceRenderer::RenderCeiling(Window* window, Player* player, Map* map)
{
    this->ceiling.clear();
    glBindTexture(GL_TEXTURE_2D, map->GetCeilingTextureID());

    for (int i = window->GetHeight(); i > window->GetHeight() / 2; i--)
    {
        double rayAngle = ((i * 2.0) / (window->GetHeight() * 1.0) - 1.0) * player->GetVerticalAngle();

        double horizontalDistToCeiling = (map->GetCeilingLevel() - player->GetZ()) / tan(rayAngle);

        double leftAngle = player->GetViewAngle() + player->GetFieldOfView() / 2.0;
        double rightAngle = player->GetViewAngle() - player->GetFieldOfView() / 2.0;

        while (leftAngle >= 2.0 * PI)
        {
            leftAngle -= 2.0 * PI;
        }
        while (leftAngle < 0.0)
        {
            leftAngle += 2.0 * PI;
        }

        while (rightAngle >= 2.0 * PI)
        {
            rightAngle -= 2.0 * PI;
        }
        while (rightAngle < 0.0)
        {
            rightAngle += 2.0 * PI;
        }

        double xLeft = player->GetX() + horizontalDistToCeiling * cos(leftAngle);
        double yLeft = player->GetY() + horizontalDistToCeiling * sin(leftAngle);

        double xRight = player->GetX() + horizontalDistToCeiling * cos(rightAngle);
        double yRight = player->GetY() + horizontalDistToCeiling * sin(rightAngle);

        this->ceiling.push_back(0.0);
        this->ceiling.push_back(i * 1.0);

        //
        this->ceiling.push_back(xLeft / (map->GetWidth() * 1.0));//
        this->ceiling.push_back(1.0 - yLeft / (map->GetHeight() * 1.0));//
        //

        this->ceiling.push_back(window->GetWidth() * 1.0);
        this->ceiling.push_back(i * 1.0);

        //
        this->ceiling.push_back(xRight / (map->GetWidth() * 1.0));//
        this->ceiling.push_back(1.0 - yRight / (map->GetHeight() * 1.0));//
        //

    }

    if (ceiling.size() > 0)
    {
        glBindVertexArray(this->ceilingVAOID);
        glBindBuffer(GL_ARRAY_BUFFER, this->ceilingVBOID);

        glBufferData(GL_ARRAY_BUFFER, sizeof(double) * this->ceiling.size(), &this->ceiling[0], GL_DYNAMIC_DRAW);

        glDrawArrays(GL_LINES, 0, ceiling.size() / 4);
    }
}

double SpaceRenderer::GetDepth(int column)
{
    if (0 <= column && column <= MAX_SCREEN_WIDTH)
    {
        return this->depthBuffer[column];
    }

    return -1.0;
}

void SpaceRenderer::SetDepth(int column, double depth)
{
    if (0 <= column && column <= MAX_SCREEN_WIDTH)
    {
        this->depthBuffer[column] = depth;
    }
}

SpaceRenderer::~SpaceRenderer()
{
    glDeleteShader(this->vertexShaderID);
    glDeleteShader(this->fragmentShaderID);
    glDeleteProgram(this->programID);

    glDeleteBuffers(1, &this->floorVBOID);
    glDeleteVertexArrays(1, &this->floorVAOID);

    glDeleteBuffers(1, &this->ceilingVBOID);
    glDeleteVertexArrays(1, &this->ceilingVAOID);

    glDeleteBuffers(1, &this->wallsVBOID);
    glDeleteVertexArrays(1, &this->wallsVAOID);
}