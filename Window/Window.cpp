#include "Window.h"

Window::Window(int width, int height, std::string title)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (width > MAX_SCREEN_WIDTH)
	{
		width = MAX_SCREEN_WIDTH;
	}

	if (height > MAX_SCREEN_HEIGHT)
	{
		height = MAX_SCREEN_HEIGHT;
	}

	this->width = width;
	this->height = height;

	this->title = title;

	this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
	//glfwGetPrimaryMonitor();

	glfwMakeContextCurrent(this->window);

	glfwSetFramebufferSizeCallback(this->window, Window::FramebufferSizeCallback);
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetTime(this->currentTime);

	glewInit();

	glfwSwapInterval(0);
}

Window::~Window()
{
	glfwDestroyWindow(this->window);
}

int Window::GetWidth()
{
	return this->width;
}

int Window::GetHeight()
{
	return this->height;
}

GLFWwindow* Window::GetWindow()
{
	return this->window;
}

double Window::GetDeltaTime()
{
	return this->deltaTime;
}

void Window::PreFrameDraw()
{
	this->previousTime = this->currentTime;
	this->currentTime = glfwGetTime();
	this->deltaTime = this->currentTime - this->previousTime;

	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::PostFrameDraw()
{
	glfwSwapBuffers(this->window);

	glfwPollEvents();
}

void Window::SetBackgroundColor(double red, double green, double blue, double alpha)
{
	glClearColor(red, green, blue, alpha);
}

void Window::SetBackgroundColor(double red, double green, double blue)
{
	glClearColor(red, green, blue, 1.0f);
}

double Window::ShowFPS()
{
	return 1.0 / this->deltaTime;
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}

bool Window::ShouldWindowClose()
{
	return glfwWindowShouldClose(this->window);
}

void Window::SetWindowShouldClose(bool state)
{
	glfwSetWindowShouldClose(this->window, state);
}