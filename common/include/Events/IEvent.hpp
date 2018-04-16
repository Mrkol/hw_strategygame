#pragma once

#ifndef COMMON_EVENTS_IEVENT_HPP_
#define COMMON_EVENTS_IEVENT_HPP_

#include <vector>

class EventArg
{

};

class IEvent
{
public:
	virtual void Subscribe(bool (*)(EventArg&)) = 0;
	virtual bool Unsubscribe(bool (*)(EventArg&)) = 0;
	virtual void Happen(EventArg&) = 0; // Call all subscribers no matter what
	virtual bool TryHappen(EventArg&) = 0; // Stop and reeturn false if one of subscribers returned false
private:
	
};
#endif //COMMON_EVENTS_IEVENT_HPP_
