#include "Program.hpp"

#include <cassert>
#include <vector>

#include "g3log/g3log.hpp"
#include "glad/glad.h"

namespace engine
{
	Program::Program(Shader& vShader, Shader& fShader)
	{
		assert(vShader.good());
		assert(fShader.good());
		assert(vShader.getShaderType() == GL_VERTEX_SHADER);
		assert(fShader.getShaderType() == GL_FRAGMENT_SHADER);

		programID = glCreateProgram();
		glAttachShader(programID, vShader.shaderID);
		glAttachShader(programID, fShader.shaderID);
		glLinkProgram(programID);

		GLint isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int*) &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLenght = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLenght);

			std::vector<GLchar> infoLog(maxLenght);
			glGetProgramInfoLog(programID, maxLenght, &maxLenght, &infoLog[0]);

			LOG(WARNING) << "Failed linking ";
			LOG(WARNING) << &infoLog[0];

			glDeleteProgram(programID);
			programID = 0;
			return;
		}
		glDetachShader(programID, vShader.shaderID);
		glDetachShader(programID, fShader.shaderID);
	}

	Program::~Program()
	{
		if (programID)
			glDeleteProgram(programID);
	}

	Program::Program(Program&& other) noexcept: programID(other.programID)
	{
		other.programID = 0;
	}

}	// namespace engine
