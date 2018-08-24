#include "RenderObject.hpp"

#include "Transform3D.hpp"
#include "TreeItem.hpp"

using namespace utils;
namespace engine
{
	void RenderObject::setTreeItem(TreeItem<std::unique_ptr<RenderObject>>* item)
	{
		treeItem = item;
		transform.setParentGetter([item]() -> Transform3D* {
			if (!item || !item->getParent() || !item->getParent()->getData())
				return nullptr;
			return &item->getParent()->getData()->getTransform();
		});
	}
}	// namespace engine
