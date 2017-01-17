//
// Created by Dawid Drozd aka Gelldur on 07/11/16.
//

#pragma once

#include <memory>
#include <vector>

#include <crosslayout/geometry/Rect.h>

namespace CrossLayout
{
class TestNode
{
public:
	TestNode(const Rect<float>& box);
	~TestNode();

	const Rect<float>& getBoundingBox() const
	{
		return _box;
	}

	const Size<float>& getSize()
	{
		return _box.size;
	}

	void setPosition(const Point<float>& position);

	const Point<float>& getPosition() const
	{
		return _box.point;
	}

	TestNode* getParent() const
	{
		return _parent;
	}

	bool hasParent() const
	{
		return _parent != nullptr;
	}

	TestNode& addChild(const std::shared_ptr<TestNode>& node);

private:
	Rect<float> _box;
	TestNode* _parent = nullptr;
	std::vector<std::shared_ptr<TestNode>> _children;
};

}

