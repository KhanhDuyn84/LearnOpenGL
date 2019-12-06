#pragma once
#include "glm/glm.hpp"

enum class Camera_Movement
{
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD
};

class Camera
{
private:
	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraTarget;
	glm::vec3 m_CameraUp;
	float m_yaw;
	float m_pitch;
	float m_fov;

public:
	glm::vec3 getPosition() const;
	glm::vec3 getTarget() const;
	glm::vec3 getVectorUp() const;
	float getFov()const;

	void InputKeyBoard(Camera_Movement movement, float deltaTime);
	void InputMouse(float xoffset, float yoffset);
	void InputScroll(float yoffset);
	Camera(glm::vec3 CameraPos, glm::vec3 CameraTarget, glm::vec3 CameraUp);
	~Camera();
};

