#include "MainWindow.h"
#include "SOIL2.h"
#include "GLSLShader.h"
#include <iostream>
#include "define.h"
#include "Loader.h"
#include "FpsClass.h"
#include "MatrixHelper.h"
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
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	
	GLuint indices[] = {
		0,1,2
	};
	
	std::unique_ptr<RawModel> rawModel = Loader::LoadRawModelWithIndices(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	std::unique_ptr<RawTexture> rawTexture = Loader::LoadTexture("../Resources/images/container.jpg", 0);

	std::unique_ptr<GLSLShader> triangleShader = std::make_unique<GLSLShader>("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	triangleShader->AddUniform("MVP");


	glm::mat4 model = glm::mat4(1.0f);
	
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 MVP = glm::mat4(1.0f);
	
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f),(float) SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
	
	FpsClass fps;
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(m_MainWindow))
	{
		fps.DoFrame();
		ProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model = MatrixHelper::CreateTransformationMatrix(glm::vec3(1.0f, 0.0f, -3.0f), 0.0f, (float)glfwGetTime()*50.0f, 0.0f, 1.0f);
		MVP = projection * view * model;
		triangleShader->Use();
		triangleShader->setMat4("MVP", MVP);

		glActiveTexture(GL_TEXTURE0 + rawTexture->getTextureUnit());
		glBindTexture(GL_TEXTURE_2D, rawTexture->getTextureID());
		glBindVertexArray(rawModel->getVAOID());
		glDrawArrays(GL_TRIANGLES, 0, rawModel->getVertexCount());
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(m_MainWindow);
		glfwPollEvents();
	}
}