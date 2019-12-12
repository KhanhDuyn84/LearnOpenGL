#pragma once
#include "Noncopyable.h"
#include "RawModel.h"
#include "GLSLShader.h"
#include "RawTexture.h"
#include <vector>

class Renderer : public Noncopyable
{
private:
	Renderer();
	~Renderer();
public:
	static void DrawArrays(std::shared_ptr<RawModel> &model, std::vector<std::shared_ptr<RawTexture>> textures);
	static void DrawElements(std::shared_ptr<RawModel> &model, std::vector<std::shared_ptr<RawTexture>> textures);
};

