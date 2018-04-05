#pragma once

#ifndef COMMON_POSITION_
#define COMMON_POSITION_

#include "CommonHelper.hpp"

namespace Common
{
	using CoordinateType = float;

	struct Position
	{
		CoordinateType x;
		CoordinateType y;
	};

	inline bool operator==(const Position& first, const Position& second)
	{
		return first.x == second.x && first.y == second.y;
	}

	Position FindWay(Position from, Position to, MovementType movePoints, MovementStyleType moveStyle);
	bool IsClose(Position from, Position to);
}

#endif // COMMON_POSITION_
