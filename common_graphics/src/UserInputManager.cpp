#include "UserInputManager.hpp"



namespace Graphics
{
	UserInputManager::UserInputManager(
		Event& OnMouseMove,
		Event& OnMouseButtonDown,
		Event& OnMouseButtonUp,
		Event& OnMouseWheel,
		Event& OnMouseHWheel,
		Event& OnKeyDown,
		Event& OnKeyUp)

		:

		OnMouseMove(OnMouseMove),
		OnMouseButtonDown(OnMouseButtonDown),
		OnMouseButtonUp(OnMouseButtonUp),
		OnMouseWheel(OnMouseWheel),
		OnMouseHWheel(OnMouseHWheel),
		OnKeyDown(OnKeyDown),
		OnKeyUp(OnKeyUp)
	{

	}

	MouseMoveEventArgs::MouseMoveEventArgs(int32_t x, int32_t y)
		: X(x), Y(y)
	{

	}

	MouseButtonEventArgs::MouseButtonEventArgs(int32_t x, int32_t y, uint32_t button)
		: X(x), Y(y), Button(button)
	{

	}

	MouseWheelEventArgs::MouseWheelEventArgs(int32_t x, int32_t y, int32_t rotationDelta)
		: X(x), Y(y), RotationDelta(rotationDelta)
	{

	}

	KeyboardEventArgs::KeyboardEventArgs(SDL_Keysym key)
		: Key(key)
	{

	}
}
