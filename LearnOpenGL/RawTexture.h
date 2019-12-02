#pragma once
#include "glad/glad.h"
#include "Noncopyable.h"
class RawTexture : public Noncopyable
{
private:
	GLuint m_textureID;
	GLuint m_TextureUnit;
public:

	RawTexture(GLuint TextureID, GLuint TextureUnit)
	{
		m_textureID = TextureID;
		m_TextureUnit = TextureUnit;
	}

	GLuint getTextureID() const
	{
		return m_textureID;
	}

	GLuint getTextureUnit() const
	{
		return m_TextureUnit;
	}

	~RawTexture()
	{
		glDeleteTextures(1, &m_textureID);
		m_TextureUnit = 0;
	}
};

