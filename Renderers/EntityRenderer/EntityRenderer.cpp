#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(std::string vertexShaderAdress, std::string fragmentShaderAdress, Window* window)
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

    glGenVertexArrays(1, &this->entityVAOID);
    glGenBuffers(1, &this->entityVBOID);

    glBindVertexArray(this->entityVAOID);
    glBindBuffer(GL_ARRAY_BUFFER, this->entityVBOID);

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

void EntityRenderer::StartUsing()
{
    glUseProgram(this->programID);
}

void EntityRenderer::StopUsing()
{
    glUseProgram(0);
}

void EntityRenderer::Render(SingleTexturedNoAIEntity* entity, Window* window, SpaceRenderer* spaceRenderer, Player* player)
{
    this->entity.clear();
    glBindTexture(GL_TEXTURE_2D, entity->GetTextureID());

    double horizontalDistToPlayer = sqrt((player->GetX() - entity->GetX()) * (player->GetX() - entity->GetX()) + (player->GetY() - entity->GetY()) * (player->GetY() - entity->GetY()));
    double entityHeightOverHorizon = entity->GetZ() + entity->GetHeight() - player->GetZ();

    double verticalAngleUp = atan(entityHeightOverHorizon / horizontalDistToPlayer);

    double entityHeightSubHorizon = entity->GetZ() - player->GetZ();

    double verticalAngleDown = atan(entityHeightSubHorizon / horizontalDistToPlayer);

    double xRelativeToPlayer = entity->GetX() - player->GetX();
    double yRelativeToPlayer = entity->GetY() - player->GetY();

    double angle = atan2(sin(player->GetViewAngle()), cos(player->GetViewAngle())) - atan2(yRelativeToPlayer, xRelativeToPlayer);

    if (angle > PI)
    {
        angle -= 2.0 * PI;
    }
    if (angle < -PI)
    {
        angle += 2.0 * PI;
    }

    double entityUp = window->GetHeight() / 2.0 * (1.0 + (verticalAngleUp / player->GetVerticalAngle()));///IMP
    double entityDown = window->GetHeight() / 2.0 * (1.0 + (verticalAngleDown / player->GetVerticalAngle()));///IMP

    double entityHeight = entityUp - entityDown;
    double aspectRatio = (entity->GetTextureHeight() * 1.0) / (entity->GetTextureWidth() * 1.0);
    double entityWidth = entityHeight / aspectRatio;

    double middlePoint = (0.5 * (angle / (player->GetFieldOfView() / 2.0)) + 0.5) * window->GetWidth();
    double entityLeft = middlePoint - entityWidth / 2.0;
    double entityRight = middlePoint + entityWidth / 2.0;

    for (int i = 0; i <= entityWidth; i++)
    {
        if (horizontalDistToPlayer < spaceRenderer->GetDepth((int)entityLeft + i))
        {
            spaceRenderer->SetDepth((int)entityLeft + i, horizontalDistToPlayer);

            this->entity.push_back(entityLeft + i * 1.0);
            this->entity.push_back(entityUp);

            //
            this->entity.push_back((i * 1.0) / entityWidth);//
            this->entity.push_back(0.0);//
            //

            this->entity.push_back(entityLeft + i * 1.0);
            this->entity.push_back(entityDown);

            //
            this->entity.push_back((i * 1.0) / entityWidth);//
            this->entity.push_back(1.0);//
            //
        }
    }

    if (this->entity.size() > 0)
    {
        glBindVertexArray(this->entityVAOID);
        glBindBuffer(GL_ARRAY_BUFFER, this->entityVBOID);

        glBufferData(GL_ARRAY_BUFFER, sizeof(double) * this->entity.size(), &this->entity[0], GL_DYNAMIC_DRAW);

        glDrawArrays(GL_LINES, 0, this->entity.size() / 4);
    }
}

EntityRenderer::~EntityRenderer()
{
    glDeleteShader(this->vertexShaderID);
    glDeleteShader(this->fragmentShaderID);
    glDeleteProgram(this->programID);
}