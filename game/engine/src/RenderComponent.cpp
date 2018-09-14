#include "RenderComponent"

using namespace engine;
void Program::onPreRender()
{
	glUseProgram(programID);
	MV.bind();
	P.bind();
}

void Program::render()
{
	onPreRender();
	glDrawArrays(GL_TRIANGLES, );
	onPostRender();
}

void Program::onPostRender() {}
