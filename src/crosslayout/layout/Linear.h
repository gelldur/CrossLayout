//
// Created by Dawid Drozd aka Gelldur on 06.06.17.
//
#pragma once

#include <functional>
#include <vector>
#include <memory>

#include <crosslayout/NodeWrapperPlain.h>
#include <crosslayout/NodeGroup.h>

#include "Margin.h"

namespace CrossLayout
{
namespace Layout
{

class Linear
{
public:
	using Rect = CrossLayout::Rect<float>;
	using Size = CrossLayout::Size<float>;
	using Point = CrossLayout::Point<float>;
	using uint = unsigned int;

	enum class Orientation
	{
		horizontal, vertical
	};
	enum Gravity
	{
		left = 1,
		right = 2,
		centerHorizontal = 3,
		top = 4,
		bottom = 8,
		centerVertical = 12,
		center = 15
	};

	template<class T>
	struct Help
	{
		Layout::Linear& layout;

		Help(Layout::Linear& layout)
				: layout(layout)
		{
		}

		void add(T item, Margin margin = {})
		{
			layout.addItem<T>(item, margin);
		}
	};

	Linear() = default;

	Linear(Orientation orientation, int gravity = (Gravity::left | Gravity::top))
			: _orientation(orientation)
			, _gravity(gravity)
	{
	}

	template<class T>
	void addItem(T item, Margin margin = {})
	{
		_items.emplace_back(item.getBoundingBox());
		_updatePositions.emplace_back([item](const Point& position) mutable
									  {
										  item.setPosition(position);
									  });
		_margins.emplace_back(margin);
	}

	template<class T>
	void nest(T layout)
	{
		//TODO enable_if
		assert(layout.pleaseConsiderMeAsLayout());

		layout.layout();
		NodeGroup nodePack = layout.getNodePack();
		_items.emplace_back(nodePack.getBoundingBox());
		_updatePositions.emplace_back([nodePack](const Point& position) mutable
									  {
										  nodePack.setPosition(position);
									  });
		_margins.emplace_back();
	}

	Size getSize();

	void setOrientation(Orientation orientation);
	void setGravity(Gravity gravity);

	void setAvailableSpace(Size size);

	void layout();
	void layout(Size size);

	NodeGroup getNodePack();

	//Helper method
	bool pleaseConsiderMeAsLayout()
	{
		return true;
	}

private:
	Orientation _orientation = Orientation::horizontal;
	int _gravity = Gravity::left | Gravity::top;//Bit flags
	Size _availableSize;
	Size _itemsTotalSize;

	std::vector<NodeWrapper<Rect>> _items;
	std::vector<Margin> _margins;

	std::vector<std::function<void(const Point&)>> _updatePositions;

	bool validate() const;

	void onMeasure();

	void onLayout();
	void onLayoutHorizontal();
	void onLayoutVertical();

	void updatePositions();
};

}
}
