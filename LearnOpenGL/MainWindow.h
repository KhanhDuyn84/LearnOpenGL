#pragma once
#include "glad/glad.h"
#include <memory>
#include "GLFW/glfw3.h"
#include "Noncopyable.h"
#include "Camera.h"
class MainWindow : public Noncopyable
{
private:
	GLFWwindow *m_MainWindow;


	void InitGLFWWindow();
	void CreateGLFWWindow();
	void InitGlad();
	void ProcessInput(float deltaTime);

	//Call back func
	void SetUpCallBackFunc();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow *window, double xoffset,double yoffset);
	static float lastX, lastY;
	static bool firstMouse;
	static std::unique_ptr<Camera> m_Camera;
public:
	MainWindow();	
	~MainWindow();

	void Run();
};

