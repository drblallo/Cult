//
// Created by massimo on 05/08/18.
//

#ifndef CULT_TREE_HPP
#define CULT_TREE_HPP

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>

namespace Utils
{
	template<typename T>
	class TreeItem
	{
		public:
		explicit TreeItem(const T& newData): parent(), children(), data(newData){};
		TreeItem& operator=(const TreeItem<T>& other) = delete;
		TreeItem(const TreeItem<T>& other)						= delete;

		TreeItem<T>* getParent() const { return parent; }

		unsigned long getChildCount() const { return children.size(); }

		std::vector<TreeItem<T>*> getChildren() const
		{
			std::vector<TreeItem<T>*> toReturn;

			for (const auto& child : children)
				toReturn.push_back(child.first);

			return toReturn;
		}

		bool hasChild(TreeItem& t) const
		{
			return children.find(&t) != children.end();
		}

		const T& getData() const { return data; }

		T& getData() { return data; }

		void setData(const T& newData) { data = newData; }

		bool isAncestor(TreeItem<T>& descendant)
		{
			TreeItem<T>* des(&descendant);
			while (des)
			{
				if (des == this)
					return true;

				des = des->getParent();
			}
			return false;
		}

		std::unique_ptr<TreeItem<T>> removeFromParent()
		{
			assert(parent != nullptr);
			auto childSet(&parent->children);
			assert(getParent()->hasChild(*this));

			std::unique_ptr<TreeItem<T>> ptr(std::move(childSet->at(this)));
			childSet->erase(this);
			parent = nullptr;
			return ptr;
		}

		TreeItem<T>& addChild(std::unique_ptr<TreeItem<T>>& child) {
			addChild(std::move(child));
		}

		TreeItem<T>& addChild(std::unique_ptr<TreeItem<T>>&& child)
		{
			assert(!hasChild(*child.get()));
			assert(child != nullptr);
			assert(child.get() != this);
			assert(!child->isAncestor(*this));
			assert(child->parent == nullptr);

			TreeItem<T>* ptr(child.get());
			child->parent = this;
			children.emplace(child.get(), std::move(child));
			return *ptr;
		}

		TreeItem<T>& addChild(const T& data)
		{
			return addChild(std::make_unique<TreeItem<T>>(data));
		}

		private:
		TreeItem<T>* parent;
		std::map<TreeItem<T>*, std::unique_ptr<TreeItem<T>>> children;
		T data;
	};

	template<typename T>
	class Tree
	{
		public:
		explicit Tree(const T& rootData)
				: root(std::make_unique<TreeItem<T>>(rootData)) {}

		TreeItem<T>& getRoot() const { return *root; }
		void setRoot(const T& data) { root.reset(new TreeItem<T>(data)); }

		private:
		std::unique_ptr<TreeItem<T>> root;
	};
}	// namespace Utils

#endif	// CULT_TREE_HPP
