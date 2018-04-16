#pragma once

#ifndef COMMON_EVENTS_CDEFAULT_EVENT_HPP_
#define COMMON_EVENTS_CDEFAULT_EVENT_HPP_

#include "CommonHelper.hpp"
#include "IEvent.hpp"
#include <list>
#include <functional>


class CDefaultEvent : public IEvent
{
public:
	virtual void Subscribe(bool (*)(EventArg&)) override;
	virtual bool Unsubscribe(bool (*)(EventArg&)) override;
	virtual void Happen(EventArg&) override;
	virtual bool TryHappen(EventArg&) override;
private:
	std::list<bool (*)(EventArg&)> subscribers_;
};
#endif //COMMON_EVENTS_CDEFAULT_EVENT_HPP_
