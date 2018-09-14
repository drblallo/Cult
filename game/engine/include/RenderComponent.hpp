#ifndef CULT_TREE_HPP
#define CULT_TREE_HPP

#include "Buffer.hpp"
#include "ProgramUniform.hpp"

namespace
{
	class RenderObject;
	class RenderComponent
	{
		protected:
		RenderComponent(RenderObject& obj): object(obj) {}
		inline RenderObject& getRenderObject() const { return object; }

		void render();

		private:
		void onPreRender();
		void onPostRender();
		ProgramUniform<glm::mat4> MV;
		ProgramUniform<glm::mat4*> P;
		Buffer buffer;
		RenderObject& object;
		~RenderComponent();
	};
}	// namespace
#endif
