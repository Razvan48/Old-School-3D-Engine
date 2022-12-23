#pragma once

#include "../Constants/Constants.h"

#include <glew.h>
#include <glfw3.h>

#include <iostream>

#include <string>

class Window
{
private:

	int width;
	int height;

	std::string title;

	GLFWwindow* window;

	double currentTime = 0.0;
	double previousTime = 0.0;

	double deltaTime = 0.0;

private:

	static void FramebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight);

public:

	Window(int width, int height, std::string title);

	~Window();

	int GetWidth();
	int GetHeight();

	GLFWwindow* GetWindow();

	double GetDeltaTime();

	void PreFrameDraw();
	void PostFrameDraw();

	void SetBackgroundColor(double red, double green, double blue, double alpha);
	void SetBackgroundColor(double red, double green, double blue);

	double ShowFPS();

	bool ShouldWindowClose();

	void SetWindowShouldClose(bool state);
};