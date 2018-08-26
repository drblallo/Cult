#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

namespace engine
{
	class Shader
	{
		public:
		Shader(const std::string& program, GLenum shaderTyoe);
		~Shader();
		Shader(const Shader& other);
		Shader(Shader&& other) noexcept;
		Shader& operator=(const Shader& other);
		bool good() const { return shaderID; }
		// methods

		private:
		// members
		GLuint shaderID;

		// helpers
	};

}	// namespace engine
#endif /* SHADER_H */
