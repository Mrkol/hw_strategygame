#pragma once

#ifndef COMMON_GRAPHICS_USER_INPUT_MANAGER_HPP__
#define COMMON_GRAPHICS_USER_INPUT_MANAGER_HPP__

#include "Events/event.hpp"
#include "Events/EventAccessProxy.hpp"
#include "SDL.hpp"


namespace Graphics
{
	using namespace Common::Events;

	class UserInputManager
	{
	public:
		UserInputManager(
			Event& OnMouseMove,
			Event& OnMouseButtonDown,
			Event& OnMouseButtonUp,
			Event& OnMouseWheel,
			Event& OnMouseHWheel,
			Event& OnKeyDown,
			Event& OnKeyUp);

		EventAccessProxy OnMouseMove;
		EventAccessProxy OnMouseButtonDown;
		EventAccessProxy OnMouseButtonUp;
		EventAccessProxy OnMouseWheel;
		EventAccessProxy OnMouseHWheel;

		EventAccessProxy OnKeyDown;
		EventAccessProxy OnKeyUp;
	};

	class MouseMoveEventArgs : public EventArgs
	{
	public:
		MouseMoveEventArgs(int32_t x, int32_t y);

		int32_t X;
		int32_t Y;
	};

	class MouseButtonEventArgs : public EventArgs
	{
	public:
		MouseButtonEventArgs(int32_t x, int32_t y, uint32_t button);

		int32_t X;
		int32_t Y;
		uint32_t Button;
	};

	class MouseWheelEventArgs : public EventArgs
	{
	public:
		MouseWheelEventArgs(int32_t x, int32_t y, int32_t rotationDelta);

		int32_t X;
		int32_t Y;
		int32_t RotationDelta;
	};

	class KeyboardEventArgs : public EventArgs
	{
	public:
		KeyboardEventArgs(SDL_Keysym key);

		SDL_Keysym Key;
	};
};

#endif // COMMON_GRAPHICS_USER_INPUT_MANAGER_HPP__
