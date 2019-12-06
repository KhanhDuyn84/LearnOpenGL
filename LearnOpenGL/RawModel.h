#pragma once
#include "glad/glad.h"
#include "Noncopyable.h"
class RawModel : public Noncopyable
{
private:
	GLuint m_VAOID;
	GLuint m_VertexCount;
public:
	
	RawModel(GLuint VAOID, GLuint VertexCount)
	{
		m_VAOID = VAOID;
		m_VertexCount = VertexCount;
	}

	GLuint getVAOID()const
	{
		return m_VAOID;
	}

	GLuint getVertexCount()const
	{
		return m_VertexCount;
	}

	~RawModel()
	{
		m_VertexCount = 0;
	}
};

