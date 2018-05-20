#include "Camera.hpp"


namespace Graphics
{
	Camera::Camera(int viewportWidth, int viewportHeight)
		: viewportWidth_(viewportWidth),
		viewportHeight_(viewportHeight),
		scale_(1),
		x_(0),
		y_(0)
	{

	}

	Common::MapPosition Camera::ToMapSpace(int x, int y)
	{
		return 
			{
				(x - viewportWidth_/2) / scale_ + x_,
				(y - viewportHeight_/2) / scale_ + y_
			};
	}

	std::pair<int, int> Camera::ToScreenSpace(Common::MapPosition position)
	{
		return std::make_pair(
			viewportWidth_/2 + (position.x - x_) * scale_,
			viewportHeight_/2 + (position.y - y_) * scale_
			);
	}


	void Camera::Move(int newX, int newY)
	{
		x_ = newX;
		y_ = newY;
	}

	void Camera::SetScale(float scale)
	{
		scale_ = scale;
	}

	void Camera::IncrementScale(float delta)
	{
		scale_ += delta;
	}

	float Camera::GetScale()
	{
		return scale_;
	}

	void Camera::Shift(int deltaX, int deltaY)
	{
		x_ += deltaX;
		y_ += deltaY;
	}

	void Camera::SetViewport(int viewportWidth, int viewportHeight)
	{
		viewportWidth_ = viewportWidth;
		viewportHeight_ = viewportHeight;
	}

	Common::MapPosition Camera::GetPosition()
	{
		return {Common::CoordinateType(x_), Common::CoordinateType(y_)};
	}
}
