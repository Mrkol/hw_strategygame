#pragma once

#ifndef COMMON_EVENTS_CANCELLABLE_EVENT_HPP_
#define COMMON_EVENTS_CANCELLABLE_EVENT_HPP_

#include "Events/event.hpp"

namespace Common { namespace Events
{
	enum class EventStatus
	{
		Active, Cancelled, Terminated
	};

	class CancellableEventArgs : public EventArgs
	{
	public:
		void CancelEvent();
		void ReactivateEvent();
		void TerminateEvent();
		EventStatus GetEventStatus();

	protected:
		EventStatus status_;
	};

	class CancellableEvent : public Event
	{
	public:
		virtual void Trigger(EventArgs&) override;

		virtual ~Event() = default;
	};
} }

#endif //COMMON_EVENTS_CANCELLABLE_EVENT_HPP_
