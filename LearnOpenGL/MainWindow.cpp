#include "MainWindow.h"
#include "SOIL2.h"
#include "GLSLShader.h"
#include <iostream>
#include "define.h"
#include "Loader.h"
#include "FpsClass.h"
#include "MatrixHelper.h"

bool MainWindow::firstMouse = true;
float MainWindow::lastX = SCR_WIDTH / 2;
float MainWindow::lastY = SCR_HEIGHT / 2;
std::unique_ptr<Camera> MainWindow::m_Camera = nullptr;

void MainWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void MainWindow::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		lastX = xpos;
		lastY = ypos;

		m_Camera->InputMouse(xoffset, yoffset);
	}
	else
	{
		firstMouse = true;
	}
}

void MainWindow::scroll_callback(GLFWwindow *window, double xoffset,double yoffset)
{
	m_Camera->InputScroll(yoffset);
}

void MainWindow::SetUpCallBackFunc()
{
	glfwSetFramebufferSizeCallback(m_MainWindow, framebuffer_size_callback);
	glfwSetCursorPosCallback(m_MainWindow, mouse_callback);
	glfwSetScrollCallback(m_MainWindow, scroll_callback);
}

MainWindow::MainWindow()
{
	InitGLFWWindow();

	CreateGLFWWindow();

	InitGlad();

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	SetUpCallBackFunc();

	m_Camera = std::make_unique<Camera>(glm::vec3(0.0f,0.0f,3.0f), glm::vec3(0.0f,0.0f,-1.0f), glm::vec3(0.0f,1.0f,0.0f));
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

void MainWindow::ProcessInput(float deltaTime)
{
	float cameraSpeed = 0.05f;
	if (glfwGetKey(m_MainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_MainWindow, GL_TRUE);
	}
	if (glfwGetKey(m_MainWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Camera->InputKeyBoard(Camera_Movement::FORWARD,deltaTime);
	}
	if (glfwGetKey(m_MainWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Camera->InputKeyBoard(Camera_Movement::BACKWARD, deltaTime);
	}
	if (glfwGetKey(m_MainWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Camera->InputKeyBoard(Camera_Movement::LEFT, deltaTime);
	}
	if (glfwGetKey(m_MainWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Camera->InputKeyBoard(Camera_Movement::RIGHT, deltaTime);
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
	
	std::unique_ptr<RawModel> rawModel = Loader::LoadRawModelWithVertices(vertices, sizeof(vertices) / sizeof(vertices[0]));
	//std::unique_ptr<RawModel> rawModel = Loader::LoadObjModel("../Resources/images/cube.obj");
	std::unique_ptr<RawTexture> rawTexture = Loader::LoadTexture("../Resources/images/container.jpg", 0);

	std::unique_ptr<GLSLShader> triangleShader = std::make_unique<GLSLShader>("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	triangleShader->AddUniform("MVP");
	
	    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3 (2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
	 };
	FpsClass fps;
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(m_MainWindow))
	{
		fps.DoFrame();
		std::cout << fps.getFPS() << std::endl;
		ProcessInput(fps.getDeltaTime());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = MatrixHelper::CreateViewMatrix(m_Camera);
		glm::mat4 projection = MatrixHelper::CreateProjectionMatrix(m_Camera);

		glActiveTexture(GL_TEXTURE0 + rawTexture->getTextureUnit());
		glBindTexture(GL_TEXTURE_2D, rawTexture->getTextureID());
		glBindVertexArray(rawModel->getVAOID());
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glm::mat4 MVP = projection * view * model;
			triangleShader->Use();
			triangleShader->setMat4("MVP", MVP);
			glDrawArrays(GL_TRIANGLES, 0, rawModel->getVertexCount());
			//glDrawElements(GL_TRIANGLES, rawModel->getVertexCount(), GL_UNSIGNED_INT, 0);

		}
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(m_MainWindow);
		glfwPollEvents();
	}

	Loader::CleanUp();
}