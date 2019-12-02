#pragma once
#include "glad/glad.h"
#include "Noncopyable.h"
class RawModel : public Noncopyable
{
private:
	GLuint m_VAOID;
	GLuint m_VBOID;
	GLuint m_EBOID;
	GLuint m_VertexCount;
public:
	
	RawModel(GLuint VAOID, GLuint VBOID, GLuint EBOID, GLuint VertexCount)
	{
		m_VAOID = VAOID;
		m_VBOID = VBOID;
		m_EBOID = EBOID;
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
		glDeleteVertexArrays(1, &m_VAOID);
		glDeleteBuffers(1, &m_VBOID);
		glDeleteBuffers(1, &m_EBOID);
		m_VertexCount = 0;
	}
};

