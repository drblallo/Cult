//
// Created by massimo on 03/08/18.
//

#include "Renderer.hpp"

#include <cassert>
#include <g3log/g3log.hpp>

namespace engine
{
	void Renderer::render() {}
	RenderObjectHandle Renderer::add(std::unique_ptr<RenderObject>&& obj)
	{
		assert(obj.get() != nullptr);
		LOG(DEBUG) << "New render object added to renderer";
		drawable.push_back(obj.get());
		return RenderObjectHandle(&hierarchy.getRoot().addChild(std::move(obj)));
	}

	RenderObjectHandle Renderer::add(std::unique_ptr<RenderObject>& obj)
	{
		return add(std::move(obj));
	}

	std::unique_ptr<RenderObject> Renderer::remove(RenderObjectHandle handle)
	{
		assert(handle.get() != getRenderObjectRoot().get());
		assert(hierarchy.getRoot().isAncestor(*handle.getItem()));

		LOG(DEBUG) << "Render object removed from renderer";

		auto item = handle.getItem()->removeFromParent();
		return std::move(item->getData());
	}

}	// namespace engine
