#pragma once

#ifndef COMMON_GRAPHICS_CAMERA_HPP_
#define COMMON_GRAPHICS_CAMERA_HPP_

#include "MapPosition.hpp"

namespace Graphics
{
	class Camera
	{
	public:
		Camera(int viewportWidth, int viewportHeight);

		Common::MapPosition ToMapSpace(int x, int y);
		std::pair<int, int> ToScreenSpace(Common::MapPosition position);

		void Move(int newX, int newY);

		void SetScale(float scale);

		void IncrementScale(float delta);

		float GetScale();

		void Shift(int deltaX, int deltaY);

		void SetViewport(int viewportWidth, int viewportHeight);

		Common::MapPosition GetPosition();

	private:
		int viewportWidth_;
		int viewportHeight_;

		float scale_;

		int x_;
		int y_;
	};
}

#endif // COMMON_GRAPHICS_CAMERA_HPP_
