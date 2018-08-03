//
// Created by massimo on 03/08/18.
//

#ifndef CULT_RENDERER_HPP
#define CULT_RENDERER_HPP
#include <memory>
#include <vector>

#include "RenderObject.hpp"

namespace GEngine
{
	class Renderer
	{
		public:
		void render();

		private:
		std::vector<std::unique_ptr<RenderObject> > drawable;
	};
}	// namespace GEngine

#endif	// CULT_RENDERER_HPP
