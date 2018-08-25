#include "RenderObject.hpp"

#include "Transform3D.hpp"

using namespace utils;
namespace engine
{
	void RenderObject::setHandle(RenderObjectHandle item)
	{
		handle = item;
		transform.setParentGetter([item]() -> Transform3D* {
			if (!item.get() || !item.getParent().get())
				return nullptr;
			return &item.getParent()->getTransform();
		});
	}
}	// namespace engine
