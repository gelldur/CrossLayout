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
 *	composer.center(bar).in(foo).center();
 *	composer.center(bar).inParent().center();
 *
 *	composer.leftEdge(foo).moveTo().leftEdge(bar);
 *	composer.leftEdge(foo).moveTo().leftEdge(bar, 10);
 *
 *	composer.topEdge(foo).moveTo().bottomEdge(bar);
 *
 *	composer.leftEdge(foo).moveTo().rightEdge(bar);
 *	composer.leftEdge(foo).moveTo().parentLeftEdge();
 *	composer.topEdge(foo).moveTo().parentBottomEdge();
 *
 *	composer.center(foo).inParent().horizontally();
 *	composer.center(foo).in(bar).horizontally();
 *	composer.center(foo).in(bar).vertically(5);
 *
 *	composer.center(foo).in(bar).center();
 *	composer.center(foo).in(bar).horizontally();
 *
 */
template<class T>
class Composer
{
private:
	class In;

	class Where;

	class Orientation;

	class WhereVertical;

	class WhereHorizontal;

	class MoveHorizontal;

	class MoveVertical;

public:
	constexpr MoveHorizontal leftEdge(typename T::wrap_t* const node) const
	{
		return Composer::MoveHorizontal(T::wrap(node), {0, 0});
	}

	constexpr MoveHorizontal rightEdge(typename T::wrap_t* const node) const
	{
		return Composer::MoveHorizontal(T::wrap(node), {1, 0});
	}

	constexpr MoveVertical topEdge(typename T::wrap_t* const node) const
	{
		return Composer::MoveVertical(T::wrap(node), {0, 1});
	}

	constexpr MoveVertical bottomEdge(typename T::wrap_t* const node) const
	{
		return Composer::MoveVertical(T::wrap(node), {0, 0});
	}

	constexpr In center(typename T::wrap_t* const node) const
	{
		return Composer::In(T::wrap(node));
	}

	static void moveByVector(T& node, const Point<float>& moveBy)
	{
		node.setPosition(moveBy + node.getPosition());
	}

private:
	struct In
	{
		friend class Composer;

		Orientation in(typename T::wrap_t* node)
		{
			return Orientation(_whatNode, T::wrap(node));
		}

		Orientation inParent()
		{
			return Orientation(_whatNode, _whatNode.getParent());
		}

	private:
		T _whatNode;

		explicit constexpr In(const T& whatNode)
				: _whatNode(whatNode)
		{
		}
	};

	struct Orientation
	{
		friend class Composer::In;

		void horizontally(const float margin = 0)
		{
			auto fromPoint = _whatNode.getBoundingBox().getPoint(0.5F, 0);
			auto toPoint = _whereNode.getBoundingBox().getPoint(0.5F, 0);
			toPoint.x += margin;
			toPoint.y = fromPoint.y;//Don't change Y position

			Composer::moveByVector(_whatNode, toPoint - fromPoint);
		}

		void vertically(const float margin = 0)
		{
			auto fromPoint = _whatNode.getBoundingBox().getPoint(0, 0.5F);
			auto toPoint = _whereNode.getBoundingBox().getPoint(0, 0.5F);
			toPoint.x = fromPoint.x;//Don't change X position
			toPoint.y += margin;

			Composer::moveByVector(_whatNode, toPoint - fromPoint);
		}

		void center()
		{
			auto fromPoint = _whatNode.getBoundingBox().getPoint(0.5F, 0.5F);
			auto toPoint = _whereNode.getBoundingBox().getPoint(0.5F, 0.5F);

			Composer::moveByVector(_whatNode, toPoint - fromPoint);
		}

	private:
		T _whatNode;
		T _whereNode;

		constexpr Orientation(const T& whatNode, const T& whereNode)
				: _whatNode(whatNode)
				, _whereNode(whereNode)
		{
		}

	};

	struct MoveHorizontal
	{
		friend class Composer;

		WhereHorizontal moveTo() const
		{
			return WhereHorizontal(_whatNode, _whatEdge);
		}

	private:
		const Point<float> _whatEdge;
		T _whatNode;

		constexpr MoveHorizontal(const T& whatNode, const Point<float>& whatEdge)
				: _whatEdge(whatEdge)
				, _whatNode(whatNode)
		{
		}
	};

	struct MoveVertical
	{
		friend class Composer;

		WhereVertical moveTo()
		{
			return WhereVertical(_whatNode, _whatEdge);
		}

	private:
		const Point<float> _whatEdge;
		T _whatNode;

		constexpr MoveVertical(const T& whatNode, const Point<float>& whatEdge)
				: _whatEdge(whatEdge)
				, _whatNode(whatNode)
		{
		}
	};

	class Where
	{
	public:
		constexpr Where(const T& whatNode, const Point<float>& whatEdge)
				: _whatEdge(whatEdge)
				, _whatNode(whatNode)
		{
		}

		void moveToPoint(const Point<float>& toPoint)
		{
			auto fromPoint = _whatNode.getBoundingBox().getPoint(_whatEdge.x, _whatEdge.y);
			Composer::moveByVector(_whatNode, toPoint - fromPoint);
		}

	public:
		const Point<float> _whatEdge;
		T _whatNode;
	};

	struct WhereHorizontal : public Where
	{
		friend class Composer::MoveHorizontal;

		void leftEdge(typename T::wrap_t* node, const float margin = 0)
		{
			auto toPoint = T::wrap(node).getBoundingBox().getPoint(0, 0);
			toPoint.x += margin;
			toPoint.y = Where::_whatNode.getPosition().y;//Don't change Y position

			Where::moveToPoint(toPoint);
		}

		void rightEdge(typename T::wrap_t* node, const float margin = 0)
		{
			auto toPoint = T::wrap(node).getBoundingBox().getPoint(1, 0);
			toPoint.x -= margin;
			toPoint.y = Where::_whatNode.getPosition().y;//Don't change Y position

			Where::moveToPoint(toPoint);
		}

		void parentLeftEdge(const float margin = 0)
		{
			auto fromPoint = Where::_whatNode.getPosition();
			auto toPoint = decltype(fromPoint){0, fromPoint.y};//Don't change Y position
			toPoint.x += margin;

			Where::moveToPoint(toPoint);
		}

		void parentRightEdge(const float margin = 0)
		{
			auto fromPoint = Where::_whatNode.getPosition();
			auto toPoint = decltype(fromPoint)
					{Where::_whatNode.getParent()->getBoundingBox().size.width, fromPoint.y};//Don't change Y position
			toPoint.x -= margin;

			Where::moveToPoint(toPoint);
		}

	private:
		constexpr WhereHorizontal(const T& whatNode, const Point<float>& whatEdge)
				: Where(whatNode, whatEdge)
		{
		}
	};

	struct WhereVertical : public Where
	{
		friend class Composer::MoveVertical;

		void topEdge(typename T::wrap_t* node, const float margin = 0)
		{
			auto toPoint = T::wrap(node).getBoundingBox().getPoint(0, 1);
			toPoint.x = Where::_whatNode.getPosition().x;//Don't change X position
			toPoint.y -= margin;

			Where::moveToPoint(toPoint);
		}

		void bottomEdge(typename T::wrap_t* node, const float margin = 0)
		{
			auto toPoint = T::wrap(node).getBoundingBox().getPoint(0, 0);
			toPoint.x = Where::_whatNode.getPosition().x;//Don't change X position
			toPoint.y += margin;

			Where::moveToPoint(toPoint);
		}

		void parentTopEdge(const float margin = 0)
		{
			auto fromPoint = Where::_whatNode.getPosition();
			auto toPoint = decltype(fromPoint)
					{fromPoint.x
							, Where::_whatNode.getParent().getBoundingBox().size.height}; //Don't change X position
			toPoint.y -= margin;

			Where::moveToPoint(toPoint);
		}

		void parentBottomEdge(const float margin = 0)
		{
			auto fromPoint = Where::_whatNode.getPosition();
			auto toPoint = decltype(fromPoint){fromPoint.x, 0}; //Don't change X position
			toPoint.y += margin;

			Where::moveToPoint(toPoint);
		}

	private:
		constexpr WhereVertical(const T& whatNode, const Point<float>& whatEdge)
				: Where(whatNode, whatEdge)
		{
		}
	};
};

}