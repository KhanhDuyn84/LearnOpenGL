#version 330 core

in vec2 pass_aTexCoords;

uniform sampler2D TextureSampler;

out vec4 FragColor;

void main()
{
	 FragColor = texture(TextureSampler,pass_aTexCoords);
}