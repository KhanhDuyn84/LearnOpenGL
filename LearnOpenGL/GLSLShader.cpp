#include "GLSLShader.h"

#include "glad/glad.h"

#include <fstream>
#include <sstream>
#include <iostream>

GLSLShader::GLSLShader(const char* vertexPath, const char* fragmentPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	CompileShader(vertexCode, fragmentCode);
}

GLSLShader::~GLSLShader()
{
	glDeleteShader(m_ID);
}

void GLSLShader::AddUniform(std::string uniformName)
{
	if (!isUniformExist(uniformName))
	{
		m_Uniforms[uniformName] = glGetUniformLocation(m_ID, uniformName.c_str());
	}
	else
	{
		std::cout << "UNIFORM " << uniformName << " has been exist" << std::endl;
	}
}

bool GLSLShader::isUniformExist(const std::string &uniformName)const
{
	return m_Uniforms.find(uniformName) != m_Uniforms.end();
}

void GLSLShader::Use()
{
	glUseProgram(m_ID);
}

void GLSLShader::CompileShader(std::string VertexCode, std::string FragmentCode)
{
	const char* vShaderCode = VertexCode.c_str();
	const char * fShaderCode = FragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	CheckCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	CheckCompileErrors(fragment, "FRAGMENT");
	// shader Program
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	CheckCompileErrors(m_ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void GLSLShader::CheckCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

void GLSLShader::UniformErrorPrintLog(const std::string& name) const
{
	std::cout << "UNIFORM " << name << " does not exist" << std::endl;
}

void GLSLShader::setBool(const std::string &name, bool value) const
{
	if (isUniformExist(name))
	{
		glUniform1i(m_Uniforms.at(name), (int)value);
	}
	else
	{
		UniformErrorPrintLog(name);
	}
}

void GLSLShader::setInt(const std::string &name, int value) const
{
	if (isUniformExist(name))
	{
		glUniform1i(m_Uniforms.at(name), value);
	}
	else
	{
		UniformErrorPrintLog(name);
	}
}

void GLSLShader::setFloat(const std::string &name, float value) const
{
	if (isUniformExist(name))
	{
		glUniform1f(m_Uniforms.at(name), value);
	}
	else
	{
		UniformErrorPrintLog(name);
	}
}

void GLSLShader::setVec2(const std::string &name, const glm::vec2 &value) const
{
	if (isUniformExist(name))
	{
		glUniform2fv(m_Uniforms.at(name), 1, &value[0]);
	}
	else
	{
		UniformErrorPrintLog(name);
	}
}

void GLSLShader::setVec2(const std::string &name, float x, float y) const
{
	if (isUniformExist(name))
	{
		glUniform2f(m_Uniforms.at(name), x, y);
	}
	else
	{
		UniformErrorPrintLog(name);
	}
}

void GLSLShader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	if (isUniformExist(name))
	{
		glUniform3fv(m_Uniforms.at(name), 1, &value[0]);
	}
	else
	{
		UniformErrorPrintLog(name);
	}
}

void GLSLShader::setVec3(const std::string &name, float x, float y, float z) const
{
	if (isUniformExist(name))
	{
		glUniform3f(m_Uniforms.at(name), x, y, z);
	}
	else
	{
		UniformErrorPrintLog(name);
	}
}

void GLSLShader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	if (isUniformExist(name))
	{
		glUniform4fv(m_Uniforms.at(name), 1, &value[0]);
	}
	else
	{
		UniformErrorPrintLog(name);
	}
}

void GLSLShader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
	if (isUniformExist(name))
	{
		glUniform4f(m_Uniforms.at(name), x, y, z, w);
	}
	else
	{
		UniformErrorPrintLog(name);
	}
}

void GLSLShader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	if (isUniformExist(name))
	{
		glUniformMatrix2fv(m_Uniforms.at(name), 1, GL_FALSE, &mat[0][0]);
	}
	else
	{
		UniformErrorPrintLog(name);
	}
}

void GLSLShader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	if (isUniformExist(name))
	{
		glUniformMatrix3fv(m_Uniforms.at(name), 1, GL_FALSE, &mat[0][0]);
	}
	else
	{
		UniformErrorPrintLog(name);
	}
}

void GLSLShader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	if (isUniformExist(name))
	{
		glUniformMatrix4fv(m_Uniforms.at(name), 1, GL_FALSE, &mat[0][0]);
	}
	else
	{
		UniformErrorPrintLog(name);
	}
}