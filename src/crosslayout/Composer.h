//
// Created by Dawid Drozd aka Gelldur on 02/11/16.
//

#pragma once

#include <crosslayout/NodeWrapper.h>
#include <crosslayout/geometry/Point.h>

namespace CrossLayout
{

/**
 * Sample usage
 *
 * Composer composer;
 *
 * composer.center(bar).in(foo).center();
 * composer.center(bar).inParent().center();
 *
 * composer.leftEdge(foo).moveTo().leftEdge(bar);
 * composer.leftEdge(foo).moveTo().leftEdge(bar, 10);
 *
 * composer.topEdge(foo).moveTo().bottomEdge(bar);
 *
 * composer.leftEdge(foo).moveTo().rightEdge(bar);
 * composer.leftEdge(foo).moveTo().parentLeftEdge();
 * composer.topEdge(foo).moveTo().parentBottomEdge();
 *
 * composer.center(foo).inParent().horizontally();
 * composer.center(foo).in(bar).horizontally();
 * composer.center(foo).in(bar).vertically(5);
 *
 * composer.center(foo).in(bar).center();
 * composer.center(foo).in(bar).horizontally();
 *
 */
template<class T>
class Composer
{
	using Rect = CrossLayout::Rect<float>;
	using Point = CrossLayout::Point<float>;

	class In;

	class Orientation;

	class WhereVertical;

	class WhereHorizontal;

	class MoveHorizontal;

	class MoveVertical;

public:
	constexpr MoveHorizontal leftEdge(NodeWrapper <T> node) const
	{
		return Composer::MoveHorizontal(node, {0, 0});
	}

	constexpr MoveHorizontal rightEdge(NodeWrapper <T> node) const
	{
		return Composer::MoveHorizontal(node, {1, 0});
	}

	constexpr MoveVertical topEdge(NodeWrapper <T> node) const
	{
		return Composer::MoveVertical(node, {0, 1});
	}

	constexpr MoveVertical bottomEdge(NodeWrapper <T> node) const
	{
		return Composer::MoveVertical(node, {0, 0});
	}

	constexpr In center(NodeWrapper <T> node) const
	{
		return Composer::In(node);
	}


	static void moveBy(NodeWrapper <T>& node, Point moveBy)
	{
		node.setPosition(moveBy + node.getPosition());
	}

private:
	struct In
	{
		friend class Composer;

		Orientation in(NodeWrapper <T> node)
		{
			return Orientation(_whichNode, node.getBoundingBox());
		}

		Orientation inParent()
		{
			return Orientation(_whichNode, Rect{Point{0, 0}, _whichNode.getParent().getBoundingBox().size});
		}

	private:
		NodeWrapper <T> _whichNode;

		explicit constexpr In(NodeWrapper <T> whichNode)
				: _whichNode(whichNode)
		{
		}
	};

	struct Orientation
	{
		friend class Composer::In;

		void horizontally(const float margin = 0)
		{
			auto fromPoint = _whichNode.getBoundingBox().getPoint(0.5F, 0);
			auto toPoint = _whereBox.getPoint(0.5F, 0);
			toPoint.x += margin;
			toPoint.y = fromPoint.y;//Don't change Y position

			Composer::moveBy(_whichNode, toPoint - fromPoint);
		}

		void vertically(const float margin = 0)
		{
			auto fromPoint = _whichNode.getBoundingBox().getPoint(0, 0.5F);
			auto toPoint = _whereBox.getPoint(0, 0.5F);
			toPoint.x = fromPoint.x;//Don't change X position
			toPoint.y += margin;

			Composer::moveBy(_whichNode, toPoint - fromPoint);

	private:
		Rect _whereBox;
		NodeWrapper <T> _whichNode;

		constexpr Orientation(NodeWrapper <T> whichNode, Rect whereBox)
				: _whereBox(whereBox)
				, _whichNode(whichNode)
		{
		}

		void center()
		{
			auto fromPoint = _whichNode.getBoundingBox().getPoint(0.5F, 0.5F);
			auto toPoint = _whereBox.getPoint(0.5F, 0.5F);

			Composer::moveBy(_whichNode, toPoint - fromPoint);
		}
	};

	struct MoveHorizontal
	{
		friend class Composer;

		WhereHorizontal moveTo() const
		{
			return WhereHorizontal(_whichNode, _whichEdge);
		}

	private:
		const Point _whichEdge;
		NodeWrapper <T> _whichNode;

		constexpr MoveHorizontal(NodeWrapper <T> whichNode, Point whichEdge)
				: _whichEdge(whichEdge)
				, _whichNode(whichNode)
		{
		}
	};

	struct MoveVertical
	{
		friend class Composer;

		WhereVertical moveTo()
		{
			return WhereVertical(_whichNode, _whichEdge);
		}

	private:
		const Point _whichEdge;
		NodeWrapper <T> _whichNode;

		constexpr MoveVertical(NodeWrapper <T> whichNode, Point whichEdge)
				: _whichEdge(whichEdge)
				, _whichNode(whichNode)
		{
		}
	};

	struct WhereHorizontal
	{
		friend class Composer::MoveHorizontal;

		void leftEdge(NodeWrapper <T> node, const float margin = 0)
		{
			auto fromPoint = _whichNode.getBoundingBox().getPoint(_whichEdge.x, _whichEdge.y);
			auto toPoint = node.getBoundingBox().getPoint(0, 0);
			toPoint.x += _whichEdge.x == 1 ? -margin : margin;
			toPoint.y = fromPoint.y;//Don't change Y position

			Composer::moveBy(_whichNode, toPoint - fromPoint);
		}

		void rightEdge(NodeWrapper <T> node, const float margin = 0)
		{
			auto fromPoint = _whichNode.getBoundingBox().getPoint(_whichEdge.x, _whichEdge.y);
			auto toPoint = node.getBoundingBox().getPoint(1, 0);
			toPoint.x += _whichEdge.x == 1 ? -margin : margin;
			toPoint.y = fromPoint.y;//Don't change Y position

			Composer::moveBy(_whichNode, toPoint - fromPoint);
		}

		void parentLeftEdge(const float margin = 0)
		{
			auto fromPoint = _whichNode.getBoundingBox().getPoint(_whichEdge.x, _whichEdge.y);
			auto toPoint = decltype(fromPoint){0, fromPoint.y};//Don't change Y position
			toPoint.x += _whichEdge.x == 1 ? -margin : margin;

			Composer::moveBy(_whichNode, toPoint - fromPoint);
		}

		void parentRightEdge(const float margin = 0)
		{
			auto fromPoint = _whichNode.getBoundingBox().getPoint(_whichEdge.x, _whichEdge.y);
			auto toPoint = decltype(fromPoint)
					{_whichNode.getParent().getBoundingBox().size.width
							, fromPoint.y};//Don't change Y position
			toPoint.x += _whichEdge.x == 1 ? -margin : margin;

			Composer::moveBy(_whichNode, toPoint - fromPoint);
		}

	private:
		const Point _whichEdge;
		NodeWrapper <T> _whichNode;

		constexpr WhereHorizontal(NodeWrapper <T> whichNode, Point whichEdge)
				: _whichEdge(whichEdge)
				, _whichNode(whichNode)
		{
		}
	};

	struct WhereVertical
	{
		friend class Composer::MoveVertical;

		void topEdge(NodeWrapper <T> node, const float margin = 0)
		{
			auto fromPoint = _whichNode.getBoundingBox().getPoint(_whichEdge.x, _whichEdge.y);
			auto toPoint = node.getBoundingBox().getPoint(0, 1);
			toPoint.x = fromPoint.x;//Don't change X position
			toPoint.y += _whichEdge.y == 1 ? -margin : margin;

			Composer::moveBy(_whichNode, toPoint - fromPoint);
		}

		void bottomEdge(NodeWrapper <T> node, const float margin = 0)
		{
			auto fromPoint = _whichNode.getBoundingBox().getPoint(_whichEdge.x, _whichEdge.y);
			auto toPoint = node.getBoundingBox().getPoint(0, 0);
			toPoint.x = fromPoint.x;//Don't change X position
			toPoint.y += _whichEdge.y == 1 ? -margin : margin;

			Composer::moveBy(_whichNode, toPoint - fromPoint);
		}

		void parentTopEdge(const float margin = 0)
		{
			auto fromPoint = _whichNode.getBoundingBox().getPoint(_whichEdge.x, _whichEdge.y);
			auto toPoint = decltype(fromPoint)
					{fromPoint.x //Don't change X position
							, _whichNode.getParent().getBoundingBox().size.height};
			toPoint.y += _whichEdge.y == 1 ? -margin : margin;

			Composer::moveBy(_whichNode, toPoint - fromPoint);
		}

		void parentBottomEdge(const float margin = 0)
		{
			auto fromPoint = _whichNode.getBoundingBox().getPoint(_whichEdge.x, _whichEdge.y);
			auto toPoint = decltype(fromPoint){fromPoint.x, 0}; //Don't change X position
			toPoint.y += _whichEdge.y == 1 ? -margin : margin;

			Composer::moveBy(_whichNode, toPoint - fromPoint);
		}

	private:
		const Point _whichEdge;
		NodeWrapper <T> _whichNode;

		constexpr WhereVertical(NodeWrapper <T> whichNode, Point whichEdge)
				: _whichEdge(whichEdge)
				, _whichNode(whichNode)
		{
		}
	};
};

}
