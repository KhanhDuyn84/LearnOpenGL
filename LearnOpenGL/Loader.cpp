#include "Loader.h"
#include "SOIL2.h"
std::vector<GLuint> Loader::m_ListVAO;
std::vector<GLuint> Loader::m_ListVBO;
std::vector<GLuint> Loader::m_ListEBO;
std::vector<GLuint> Loader::m_ListTextureID;

std::unique_ptr<RawTexture> Loader::LoadTexture(std::string fileName, GLuint TextureUnit, GLuint WRAP_S, GLuint WRAP_T, GLuint FILTER_MAG, GLuint FILTER_MIN)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAP_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAP_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FILTER_MAG);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FILTER_MIN);
	
	int width, height, channels;
	unsigned char* image = SOIL_load_image(fileName.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
	if (image)
	{
		if (channels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}
		else if (channels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		}
		glGenerateMipmap(0);
		SOIL_free_image_data(image);
	}
	else
	{
		std::cout << "FAILED TO LOAD IMAGE" << std::endl;
	}
	m_ListTextureID.push_back(textureID);
	std::unique_ptr<RawTexture> rawTexture = std::make_unique<RawTexture>(textureID, TextureUnit);
	return rawTexture;
}

std::unique_ptr<RawModel> Loader::LoadRawModelWithIndices(float *vertices, GLuint vertexCount, GLuint *indices, GLuint indexCount)
{
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_ListVAO.push_back(VAO);
	m_ListVBO.push_back(VBO);
	m_ListEBO.push_back(EBO);
	std::unique_ptr<RawModel> rawModel = std::make_unique<RawModel>(VAO, indexCount);

	return std::move(rawModel);
}

std::unique_ptr<RawModel> Loader::LoadRawModelWithVertices(float *vertices, GLuint vertexCount)
{
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_ListVAO.push_back(VAO);
	m_ListVBO.push_back(VBO);
	std::unique_ptr<RawModel> rawModel = std::make_unique<RawModel>(VAO, vertexCount);

	return std::move(rawModel);
}

void Loader::CleanUp()
{
	for (auto vao : m_ListVAO)
	{
		glDeleteVertexArrays(1, &vao);
	}

	for (auto vbo : m_ListVBO)
	{
		glDeleteBuffers(1, &vbo);
	}

	for (auto ebo : m_ListEBO)
	{
		glDeleteBuffers(1, &ebo);
	}

	for (auto texture : m_ListTextureID)
	{
		glDeleteTextures(1, &texture);
	}
}
