#pragma once

#ifndef COMMON_EVENTS_CDEFAULT_EVENT_HPP_
#define COMMON_EVENTS_CDEFAULT_EVENT_HPP_

#include "CommonHelper.hpp"
#include "IEvent.hpp"
#include <vector>
#include <functional>


class CDefaultEvent : public IEvent
{
public:
	virtual void Subscribe() override;
	virtual void Unsubscribe() override;
	virtual void Happen(...) override;
private:
	std::vector<std::function<void(int)>> subscribers_;
};
#endif //COMMON_EVENTS_CDEFAULT_EVENT_HPP_
