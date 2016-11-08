//
// Created by Dawid Drozd aka Gelldur on 07/11/16.
//

#include "TestNode.h"

namespace CrossLayout
{

TestNode::TestNode(const Rect<float>& box)
		: _box(box)
{
}

TestNode::~TestNode()
{
	for (auto& child : _children)
	{
		child->_parent = nullptr;
	}
}

void TestNode::setPosition(const Point<float>& position)
{
	_box.point = position;
}

TestNode& CrossLayout::TestNode::addChild(const std::shared_ptr<CrossLayout::TestNode>& node)
{
	_children.push_back(node);
	node->_parent = this;
	return *this;
}

}
