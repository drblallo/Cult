//
// Created by massimo on 03/08/18.
//

#ifndef CULT_RENDERER_HPP
#define CULT_RENDERER_HPP
#include <memory>
#include <vector>

#include "RenderObject.hpp"

namespace engine
{
	class RenderObject;
	class Renderer
	{
		friend class RenderObject;

		public:
		void render();

		private:
		void addObject(std::unique_ptr<RenderObject>&& obj);
		std::vector<std::unique_ptr<RenderObject> > drawable;
	};
}	// namespace engine

#endif	// CULT_RENDERER_HPP
