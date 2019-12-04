#pragma once
#include "Noncopyable.h"
#include "GLFW/glfw3.h"
typedef unsigned int GLuint;

class FpsClass : public Noncopyable
{
private:
	float m_deltaTime = 0.0f;
	float m_lastFrame = 0.0f;
	float m_currentFrame = 0.0f;

public:

	void DoFrame()
	{
		m_currentFrame = glfwGetTime();
		m_deltaTime = m_currentFrame - m_lastFrame;
		m_lastFrame = m_currentFrame;
	}

	GLuint getFPS()const
	{
		return (1.0 / m_deltaTime);
	}

	float getDeltaTime() const
	{
		return m_deltaTime;
	}
};