#ifndef PROGRAMUNIFORM_H
#define PROGRAMUNIFORM_H
#include <glad/glad.h>

namespace engine
{
	template<typename T>
	class ProgramUniform
	{
		friend class Program;

		public:
		ProgramUniform(GLint loc): data(), location(loc) {}

		ProgramUniform(GLint loc, T defaultData): data(defaultData), location(loc)
		{
		}

		ProgramUniform(ProgramUniform&& other)
				: data(other.data), location(other.location)
		{
			other.location = -1;
		}

		void setData(T newData) { data = newData; }

		private:
		void bind();
		T data;
		GLint location;
	};

}	// namespace engine
#endif /* PROGRAMUNIFORM_H */
