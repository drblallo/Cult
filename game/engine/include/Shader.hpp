#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

namespace engine
{
	class Shader
	{
		friend class Program;

		public:
		Shader(const std::string& program, GLenum shaderTyoe);
		~Shader();
		Shader(const Shader& other);
		Shader(Shader&& other) noexcept;
		Shader& operator=(const Shader& other);
		bool good() const { return shaderID; }
		GLenum getShaderType() const { return shaderType; }
		// methods

		private:
		// members
		GLuint shaderID;
		GLenum shaderType;

		// helpers
	};

}	// namespace engine
#endif /* SHADER_H */
