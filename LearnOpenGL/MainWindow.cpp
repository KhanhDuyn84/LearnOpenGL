#include "MainWindow.h"
#include "GLSLShader.h"
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
	float vertices[] = {
		//Position					//Color
		-0.5f, -0.5f, 0.0f,			1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,			0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,			0.0f, 0.0f, 1.0f
	};
	
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	std::unique_ptr<GLSLShader> triangleShader = std::make_unique<GLSLShader>("../Resources/Shaders/TriangleShaderVS.vs","../Resources/Shaders/TriangleShaderFS.fs");

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float currentFrame = 0.0f;
	while (!glfwWindowShouldClose(m_MainWindow))
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		std::cout << "Delta Time: " << deltaTime << "\tFPS: " << (float)1.0f / deltaTime << std::endl;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ProcessInput();
		
		triangleShader->Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(m_MainWindow);
		glfwPollEvents();
	}
}