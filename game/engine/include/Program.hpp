#ifndef PROGRAM_H
#define PROGRAM_H
#include "Shader.hpp"

namespace engine
{
	class Program
	{
		public:
		Program(Shader& vertexShader, Shader& fragShader);
		~Program();
		Program(const Program& other) = delete;
		Program(Program&& other) noexcept;
		Program& operator=(const Program& other) = delete;
		bool good() const { return programID; }
		// methods

		private:
		// members
		unsigned int programID;

		// helpers
	};

}	// namespace engine
#endif /* PROGRAM_H */
