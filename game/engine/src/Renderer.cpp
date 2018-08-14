//
// Created by massimo on 03/08/18.
//

#include "Renderer.hpp"

#include <cassert>
#include <g3log/g3log.hpp>

namespace GEngine
{
	void Renderer::render() {}
	void Renderer::addObject(std::unique_ptr<RenderObject>&& obj)
	{
		assert(std::find(drawable.begin(), drawable.end(), obj) == drawable.end());
		LOG(DEBUG) << "New render object added to renderer";
		drawable.push_back(std::move(obj));
	}

}	// namespace GEngine
