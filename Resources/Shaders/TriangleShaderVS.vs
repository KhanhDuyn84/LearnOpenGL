#version 330 core

layout (location =0) in vec3 aPos;
layout (location =1) in vec2 aTexCoords;

out vec2 pass_aTexCoords;

void main()
{
	 gl_Position = vec4(aPos, 1.0);

	 pass_aTexCoords = aTexCoords;
}