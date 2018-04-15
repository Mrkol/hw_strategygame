#pragma once

#ifndef COMMON_EVENTS_IEVENT_HPP_
#define COMMON_EVENTS_IEVENT_HPP_

#include <vector>


class IEvent
{
public:
	virtual void Subscribe() = 0;
	virtual void Unsubscribe() = 0;
	virtual void Happen(...) = 0;
private:
	
};
#endif //COMMON_EVENTS_IEVENT_HPP_
