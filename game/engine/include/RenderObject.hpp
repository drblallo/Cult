//
// Created by massimo on 03/08/18.
//

#ifndef CULT_RENDEROBJECT_HPP
#define CULT_RENDEROBJECT_HPP
#include <Transform3D.hpp>

namespace GEngine
{
	class RenderObject
	{
		friend class Renderer;

		public:
		RenderObject(): transform() {}
		virtual void draw()			= 0;
		virtual ~RenderObject() = 0;

		private:
		Transform3D transform;
	};
}	// namespace GEngine

#endif	// CULT_RENDEROBJECT_HPP
