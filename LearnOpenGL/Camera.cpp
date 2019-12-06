#include "Camera.h"



Camera::Camera(glm::vec3 CameraPos, glm::vec3 CameraTarget, glm::vec3 CameraUp)
	: m_CameraPos(CameraPos)
	, m_CameraTarget(CameraTarget)
	, m_CameraUp(CameraUp)

{
	m_yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	m_pitch = 0.0f;
	m_fov = 45.0f;
}

Camera::~Camera()
{
}

glm::vec3 Camera::getPosition() const
{
	return m_CameraPos;
}

glm::vec3 Camera::getTarget() const
{
	return m_CameraTarget;
}

glm::vec3 Camera::getVectorUp() const
{
	return m_CameraUp;
}

float Camera::getFov()const
{
	return m_fov;
}

void Camera::InputKeyBoard(Camera_Movement movement, float deltaTime)
{
	float cameraSpeed = 10.0f * deltaTime;
	if (movement == Camera_Movement::FORWARD)
	{
		m_CameraPos += cameraSpeed * glm::normalize(m_CameraTarget);
	}
	else if (movement == Camera_Movement::BACKWARD)
	{
		m_CameraPos -= cameraSpeed * m_CameraTarget;
	}
	else if (movement == Camera_Movement::LEFT)
	{
		m_CameraPos -= cameraSpeed * glm::normalize(glm::cross(m_CameraTarget,m_CameraUp));
	}
	else if (movement == Camera_Movement::RIGHT)
	{
		m_CameraPos += cameraSpeed * glm::normalize(glm::cross(m_CameraTarget, m_CameraUp));
	}
}

void Camera::InputMouse(float xoffset, float yoffset)
{
	float sensitive = 0.3f;
	xoffset *= sensitive;
	yoffset *= sensitive;
	m_yaw += xoffset;
	m_pitch += yoffset;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;

	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_CameraTarget = glm::normalize(front);
}

void Camera::InputScroll(float yoffset)
{
	if (m_fov >= 1.0f && m_fov <= 45.0f)
		m_fov -= yoffset;
	if (m_fov <= 1.0f)
		m_fov = 1.0f;
	if (m_fov >= 45.0f)
		m_fov = 45.0f;
}