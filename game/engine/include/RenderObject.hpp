//
// Created by massimo on 03/08/18.
//

#ifndef CULT_RENDEROBJECT_HPP
#define CULT_RENDEROBJECT_HPP
#include <Transform3D.hpp>
#include <memory>

#include "RenderObjectHandle.hpp"

namespace engine
{
	class Window;
	class RenderObject
	{
		friend class Renderer;

		public:
		virtual ~RenderObject() {}
		RenderObject(): transform(), handle(nullptr) {}
		Transform3D& getTransform() { return transform; }

		protected:
		virtual void draw() {}

		private:
		RenderObjectHandle getTreeItem() const { return handle; }
		void setHandle(RenderObjectHandle item);
		Transform3D transform;
		RenderObjectHandle handle;
	};
}	// namespace engine

#endif	// CULT_RENDEROBJECT_HPP
