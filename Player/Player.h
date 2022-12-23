#pragma once

#include "../Constants/Constants.h"

class Player
{
private:

	double x;
	double y;

	double viewAngle;

	double transSpeed = 10.0;

	double runToWalkRatio = 2.0;

	double runningTransSpeed = this->runToWalkRatio * this->transSpeed;
	double rotSpeed = 1.0;

	double z = 0.5;//Inaltimea jucatorului, dar si coordonata privirii pe axa verticala a lumii.

	double cursorX = 0.0;

	double fov = PI / 4.0;

	double verticalAngle = PI / 6.0;

	double bodyRadius = 0.25;

public:

	Player(double x, double y, double viewAngle);

	~Player();

	void Translate(double x, double y);

	void Rotate(double angle);

	double GetX();
	double GetY();

	void SetX(double x);
	void SetY(double y);

	double GetBodyRadius();

	void SetBodyRadius(double bodyRadius);

	double GetViewAngle();

	double GetTransSpeed();
	double GetRotSpeed();

	double GetCursorX();
	void SetCursorX(double cursorX);

	void SetFieldOfView(double fov);
	double GetFieldOfView();

	double GetVerticalAngle();

	double GetRunningTransSpeed();

	double GetZ();
	void SetZ(double z);
};