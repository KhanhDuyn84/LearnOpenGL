#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Noncopyable.h"

class MainWindow : public Noncopyable
{
private:
	GLFWwindow *m_MainWindow;
	
	void InitGLFWWindow();
	void CreateGLFWWindow();
	void InitGlad();
	void ProcessInput();

	//Call back func
	void SetUpCallBackFunc();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
	MainWindow();	
	~MainWindow();

	void Run();
};

