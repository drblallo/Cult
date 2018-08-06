//
// Created by massimo on 05/08/18.
//

#include "TreeItem.hpp"
#include <gtest/gtest.h>

using namespace Utils;

template <typename T>
bool isTreeWellMade (TreeItem<T>* tree) {
	if (!tree)
		return true;

	for (TreeItem<T>* child : tree->getChildren())
		if (!isTreeWellMade<T>(child))
			return false;

	if (!tree->getParent())
		return true;

	return (tree->getParent()->hasChild(tree));
}

class TreeTest : public testing::Test {
 public:
	TreeTest() : tree(4) {}
	Tree<int> tree;
	virtual void SetUp()
	{

	}

	virtual void TearDown() {
		EXPECT_TRUE(isTreeWellMade<int>(&tree.getRoot()));
	}
};


TEST_F(TreeTest, defaultRootHasNoChildren) {
	EXPECT_EQ(tree.getRoot().getChildCount(), 0);
	EXPECT_EQ(tree.getRoot().getChildren().size(), 0);
}


TEST_F(TreeTest, rootCanBeSet) {
	tree.setRoot(5);
	EXPECT_EQ(tree.getRoot().getData(), 5);
}

TEST_F(TreeTest, canAddChild) {
	tree.setRoot(5);
	TreeItem<int>* t = &tree.getRoot().addChild(1);

	EXPECT_EQ(t->getData(), 1);
	EXPECT_EQ(tree.getRoot().hasChild(t), 1);
}


