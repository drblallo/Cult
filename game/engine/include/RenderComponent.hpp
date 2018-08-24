#ifndef CULT_TREE_HPP
#define CULT_TREE_HPP

namespace
{
	class RenderObject;
	class RenderComponent
	{
		protected:
		RenderComponent(RenderObject& obj): object(obj) {}
		inline RenderObject& getRenderObject() const { return object; }

		private:
		RenderObject& object;
		~RenderComponent();
	};
}	// namespace
#endif
