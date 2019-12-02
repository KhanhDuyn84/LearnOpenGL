#pragma once
#include "glad/glad.h"
#include <iostream>
#include "Noncopyable.h"
#include "RawTexture.h"
#include "RawModel.h"
class Loader : public Noncopyable
{
private:
	Loader() = default;
	~Loader() = default;
public:

	static std::unique_ptr<RawTexture> LoadTexture(std::string fileName, GLuint TextureUnit, GLuint WRAP_S = GL_REPEAT, GLuint WRAP_T = GL_REPEAT, GLuint FILTER_MAG = GL_LINEAR, GLuint FILTER_MIN = GL_LINEAR);

	static std::unique_ptr<RawModel> LoadModel(float *vertices, GLuint vertexCount, GLuint *indices, GLuint indexCount);
};

