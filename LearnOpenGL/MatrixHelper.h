#pragma once
#include "Noncopyable.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"
class MatrixHelper : public Noncopyable
{
public:
	static glm::mat4 CreateTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale)
	{
		glm::mat4 transformMatrix = glm::mat4(1.0f);

		transformMatrix = glm::translate(transformMatrix, translation);

		transformMatrix = glm::rotate(transformMatrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
		transformMatrix = glm::rotate(transformMatrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
		transformMatrix = glm::rotate(transformMatrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));

		transformMatrix = glm::scale(transformMatrix, glm::vec3(scale, scale, scale));

		return transformMatrix;
	}

	static glm::mat4 CreateViewMatrix(const std::unique_ptr<Camera> &camera)
	{
		glm::mat4 viewMatrix = glm::mat4(1.0f);

		viewMatrix = glm::lookAt(camera->getPosition(), camera->getPosition() + camera->getTarget(), camera->getVectorUp());

		return viewMatrix;
	}

	static glm::mat4 CreateProjectionMatrix(const std::unique_ptr<Camera> &camera)
	{
		glm::mat4 projection = glm::mat4(1.0f);

		projection = glm::perspective(camera->getFov(), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

		return projection;
	}
};