#include "RenderObjectHandle.hpp"

#include <cassert>

#include "RenderObject.hpp"
#include "TreeItem.hpp"
namespace engine
{
	int RenderObjectHandle::getChildCount() const { return ogg->getChildCount(); }
	RenderObjectHandle RenderObjectHandle::getChild(int child) const
	{
		return RenderObjectHandle(ogg->getChildren()[child]);
	}

	utils::TreeItem<std::unique_ptr<RenderObject>>* RenderObjectHandle::getItem()
			const
	{
		return ogg;
	}

	void RenderObjectHandle::setParent(RenderObjectHandle handle)
	{
		assert(handle.getItem()->getRoot() == getItem()->getRoot());
		assert(getItem()->getRoot() != getItem());
		auto t(getItem()->removeFromParent());
		handle.getItem()->addChild(std::move(t));
	}

	RenderObjectHandle RenderObjectHandle::getParent() const
	{
		return RenderObjectHandle(getItem()->getParent());
	}

	RenderObject* RenderObjectHandle::get() const { return ogg->getData().get(); }

	RenderObject* RenderObjectHandle::operator->() const { return get(); }
}	// namespace engine
