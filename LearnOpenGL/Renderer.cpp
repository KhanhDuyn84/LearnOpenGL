#include "Renderer.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::DrawArrays(std::shared_ptr<RawModel> &model, std::vector<std::shared_ptr<RawTexture>> textures)
{
	for (std::shared_ptr<RawTexture>& texture : textures)
	{
		glActiveTexture(GL_TEXTURE0 + texture->getTextureUnit());
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	}
	glBindVertexArray(model->getVAOID());
	glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Renderer::DrawElements(std::shared_ptr<RawModel> &model, std::vector<std::shared_ptr<RawTexture>> textures)
{
	for (std::shared_ptr<RawTexture>& texture : textures)
	{
		glActiveTexture(GL_TEXTURE0 + texture->getTextureUnit());
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	}
	glBindVertexArray(model->getVAOID());
	glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}