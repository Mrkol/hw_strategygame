#pragma once

#ifndef COMMON_EVENTS_EVENT_HPP_
#define COMMON_EVENTS_EVENT_HPP_

#include <functional>
#include <string>
#include <map>

namespace Common { namespace Events 
{
	class EventArgs
	{

	};

	using Callback = std::function<void(EventArgs&)>;

	class IEvent
	{
	public:
		virtual void Subscribe(const std::string& id, Callback callback) = 0;
		virtual bool Unsubscribe(const std::string& id) = 0;

		virtual void Trigger(EventArgs&) = 0;

		virtual ~IEvent() = default;
	};

	class Event : public IEvent
	{
	public:
		virtual void Subscribe(const std::string& id, Callback callback) override;
		virtual bool Unsubscribe(const std::string& id) override;

		virtual void Trigger(EventArgs&) override;

		virtual ~Event() = default;

	private:
		std::map<std::string, Callback> subscribers_;
	};
} }

#endif //COMMON_EVENTS_EVENT_HPP_
