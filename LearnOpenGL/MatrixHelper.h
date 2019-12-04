#pragma once
#include "Noncopyable.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
};