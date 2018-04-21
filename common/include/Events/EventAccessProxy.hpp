#pragma once

#ifndef COMMON_EVENTS_EVENT_ACCESS_PROXY_HPP_
#define COMMON_EVENTS_EVENT_ACCESS_PROXY_HPP_

#include "event.hpp"
#include <memory>

namespace Common { namespace Events
{
	class EventAccessProxy : public IEvent
	{
	public:
		EventAccessProxy(IEvent& controlled);

		virtual void Subscribe(const std::string& id, Callback callback) override;
		virtual bool Unsubscribe(const std::string& id) override;

		virtual void Trigger(EventArgs& args) override;

		virtual ~EventAccessProxy() = default;

	private:
		IEvent& controlled_;
	};
} }

#endif //COMMON_EVENTS_EVENT_ACCESS_PROXY_HPP_
