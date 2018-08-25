//
// Created by massimo on 03/08/18.
//

#ifndef CULT_RENDERER_HPP
#define CULT_RENDERER_HPP

#include <list>

#include "Camera.hpp"
#include "RenderObject.hpp"
#include "RenderObjectHandle.hpp"
#include "TreeItem.hpp"

namespace engine
{
	class RenderObject;
	class Renderer
	{
		public:
		Renderer(int width, int height)
				: camera(width, height), hierarchy(std::make_unique<RenderObject>())
		{
		}
		Renderer(Renderer&& other)
				: camera(other.camera),
					drawable(std::move(other.drawable)),
					hierarchy(std::move(other.hierarchy))
		{
		}

		void render();
		void sort();

		RenderObjectHandle add(std::unique_ptr<RenderObject>& obj);
		RenderObjectHandle add(std::unique_ptr<RenderObject>&& obj);
		std::unique_ptr<RenderObject> remove(RenderObjectHandle handle);
		RenderObjectHandle getRenderObjectRoot()
		{
			return RenderObjectHandle(&hierarchy.getRoot());
		}

		Camera& getCamera() { return camera; }

		private:
		Camera camera;
		std::list<RenderObject*> drawable;
		utils::Tree<std::unique_ptr<RenderObject>> hierarchy;
	};
}	// namespace engine

#endif	// CULT_RENDERER_HPP
