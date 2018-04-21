#pragma once

#ifndef COMMON_MAP_POSITION_HPP_
#define COMMON_MAP_POSITION_HPP_

#include "CommonHelper.hpp"

namespace Common
{
	using CoordinateType = float;

	struct MapPosition
	{
		CoordinateType x;
		CoordinateType y;
	};

	inline bool operator==(const MapPosition& first, const MapPosition& second)
	{
		return first.x == second.x && first.y == second.y;
	}

	MapPosition FindWay(MapPosition from, MapPosition to, MoveSpeedType speed, MovementType type);
	bool IsClose(MapPosition first, MapPosition second);
}

#endif // COMMON_MAP_POSITION_HPP_
