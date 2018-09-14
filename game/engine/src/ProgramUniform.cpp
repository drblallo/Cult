#include "ProgramUniform.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace engine;

template<>
void ProgramUniform<glm::mat4*>::bind()
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(*data));
}

template<>
void ProgramUniform<glm::mat4>::bind()
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
}
