#include "Shader.hpp"

#include <g3log/g3log.hpp>

namespace engine
{
	Shader::Shader(const std::string& program, GLenum sType): shaderType(sType)
	{
		shaderID = glCreateShader(shaderType);
		const char* c(program.c_str());
		glShaderSource(shaderID, 1, &c, nullptr);
		glCompileShader(shaderID);

		GLint success = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint lenght = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &lenght);
			GLchar val[lenght];
			glGetShaderInfoLog(shaderID, lenght, &lenght, val);
			glDeleteShader(shaderID);
			LOG(WARNING) << "failed compilation of " << program;
			LOG(WARNING) << val;
			shaderID = 0;
		}
	}

	Shader::~Shader()
	{
		if (shaderID)
			glDeleteShader(shaderID);
	}

	Shader::Shader(const Shader& other): shaderID(other.shaderID) {}

	Shader::Shader(Shader&& other) noexcept: shaderID(other.shaderID)
	{
		other.shaderID = 0;
	}

	Shader& Shader::operator=(const Shader& other)
	{
		shaderID = other.shaderID;
		return *this;
	}

}	// namespace engine
