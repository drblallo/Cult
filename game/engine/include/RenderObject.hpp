//
// Created by massimo on 03/08/18.
//

#ifndef CULT_RENDEROBJECT_HPP
#define CULT_RENDEROBJECT_HPP
#include <Transform3D.hpp>
#include <memory>

namespace Utils
{
	template<typename T>
	class TreeItem;
}

namespace engine
{
	class Window;
	class RenderObject
	{
		friend class Renderer;

		public:
		virtual ~RenderObject() {}
		RenderObject(): transform() {}
		Transform3D& getTransform() { return transform; }

		protected:
		virtual void draw() {}

		private:
		utils::TreeItem<std::unique_ptr<RenderObject>>* getTreeItem() const
		{
			return treeItem;
		}
		void setTreeItem(utils::TreeItem<std::unique_ptr<RenderObject>>* item);
		Transform3D transform;
		utils::TreeItem<std::unique_ptr<RenderObject>>* treeItem;
	};
}	// namespace engine

#endif	// CULT_RENDEROBJECT_HPP
