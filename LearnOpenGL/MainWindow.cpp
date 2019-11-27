#include "MainWindow.h"
#include <iostream>
#include "define.h"

void MainWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void MainWindow::SetUpCallBackFunc()
{
	glfwSetFramebufferSizeCallback(m_MainWindow, framebuffer_size_callback);
}

MainWindow::MainWindow()
{
	InitGLFWWindow();

	CreateGLFWWindow();

	InitGlad();

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	SetUpCallBackFunc();
}

MainWindow::~MainWindow()
{
	glfwDestroyWindow(m_MainWindow);
	glfwTerminate();
}

void MainWindow::InitGLFWWindow()
{
	if (!glfwInit())
	{
		std::cout << "FAILED TO INITIALIZE GLFW WINDOW" << std::endl;
		system("pause");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

void MainWindow::CreateGLFWWindow()
{
	m_MainWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);

	if (m_MainWindow == nullptr)
	{
		std::cout << "FAILED TO CREATE GLFW WINDOW" << std::endl;
		glfwTerminate();
		system("pause");
	}
	glfwMakeContextCurrent(m_MainWindow);
}

void MainWindow::InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;
		glfwTerminate();
		system("pause");
	}
}

void MainWindow::ProcessInput()
{
	if (glfwGetKey(m_MainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_MainWindow, GL_TRUE);
	}
}

void MainWindow::Run()
{
	while (!glfwWindowShouldClose(m_MainWindow))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ProcessInput();

		glfwSwapBuffers(m_MainWindow);
		glfwPollEvents();
	}
}