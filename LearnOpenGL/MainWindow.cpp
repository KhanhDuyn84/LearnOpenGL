#include "MainWindow.h"
#include "SOIL2.h"
#include "GLSLShader.h"
#include <iostream>
#include "define.h"
#include "Loader.h"
#include "FpsClass.h"
#include "MatrixHelper.h"
#include "Renderer.h"

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

void MainWindow::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
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

	m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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
		m_Camera->InputKeyBoard(Camera_Movement::FORWARD, deltaTime);
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
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	std::shared_ptr<RawModel> containerModel = Loader::LoadRawModelWithVertices(vertices, sizeof(vertices) / sizeof(vertices[0]));
	std::shared_ptr<RawTexture> containerTexture1 = Loader::LoadTexture("../Resources/images/container2.png", 0);
	std::shared_ptr<RawTexture> containerTexture2 = Loader::LoadTexture("../Resources/images/container2_specular.png", 1);
	std::shared_ptr<RawTexture> containerTexture3 = Loader::LoadTexture("../Resources/images/matrix.jpg", 2);
	std::vector<std::shared_ptr<RawTexture>> containerTextures;
	containerTextures.push_back(containerTexture1);
	containerTextures.push_back(containerTexture2);
	containerTextures.push_back(containerTexture3);
	std::unique_ptr<GLSLShader> containerShader = std::make_unique<GLSLShader>("../Resources/Shaders/ContainerShaderVS.vs", "../Resources/Shaders/ContainerShaderFS.fs");
	containerShader->AddUniform("MVP");
	containerShader->AddUniform("model");
	containerShader->AddUniform("light.position");
	containerShader->AddUniform("light.ambient");
	containerShader->AddUniform("light.diffuse");
	containerShader->AddUniform("light.specular");
	containerShader->AddUniform("material.diffuse");
	containerShader->AddUniform("material.specular");
	containerShader->AddUniform("material.emission");
	containerShader->AddUniform("material.shininess");
	containerShader->AddUniform("viewPos");

	std::shared_ptr<RawModel> lampModel = Loader::LoadRawModelWithVertices(vertices, sizeof(vertices) / sizeof(vertices[0]));
	std::vector<std::shared_ptr<RawTexture>> lampTextures;
	std::unique_ptr<GLSLShader> lampShader = std::make_unique<GLSLShader>("../Resources/Shaders/LampShaderVS.vs", "../Resources/Shaders/LampShaderFS.fs");
	lampShader->AddUniform("MVP");
	lampShader->AddUniform("lightColor");

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.2f, 0.5f, 2.0f);	
	glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);

	containerShader->Use();
	containerShader->setVec3("light.position", lightPos);
	containerShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	containerShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	containerShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	containerShader->setInt("material.diffuse", containerTexture1->getTextureUnit());
	containerShader->setInt("material.specular", containerTexture2->getTextureUnit());
	containerShader->setInt("material.emission", containerTexture3->getTextureUnit());
	containerShader->setFloat("material.shininess",32);


	lampShader->Use();
	lampShader->setVec3("lightColor",lightColor);


	FpsClass fps;
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(m_MainWindow))
	{
		fps.DoFrame();
		ProcessInput(fps.getDeltaTime());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightPos.x = sin(glfwGetTime())*2.0f;
		lightPos.z = cos(glfwGetTime())*2.0f;

		//lightColor.x = sin(glfwGetTime() * 2.0f);
		//lightColor.y = sin(glfwGetTime() * 0.7f);
		//lightColor.z = sin(glfwGetTime() * 1.3f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence

		glm::mat4 view = MatrixHelper::CreateViewMatrix(m_Camera);
		glm::mat4 projection = MatrixHelper::CreateProjectionMatrix(m_Camera);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 MVP = projection * view * model;
		containerShader->Use();
		containerShader->setMat4("MVP", MVP);
		containerShader->setMat4("model", model);
		containerShader->setVec3("viewPos", m_Camera->getPosition());
		containerShader->setVec3("light.position", lightPos);
		containerShader->setVec3("light.ambient", ambientColor);
		containerShader->setVec3("light.diffuse", diffuseColor);
		Renderer::DrawArrays(containerModel, containerTextures);


		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f,0.2f,0.2f));
		MVP = projection * view * model;
		lampShader->Use();
		lampShader->setMat4("MVP", MVP);
		lampShader->setVec3("lightColor", lightColor);
		Renderer::DrawArrays(lampModel, lampTextures);

		glfwSwapBuffers(m_MainWindow);
		glfwPollEvents();
	}

	Loader::CleanUp();
}