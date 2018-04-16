#include "Events/CDefaultEvent.hpp"

void CDefaultEvent::Happen(EventArg& args)
{
	for (auto i = subscribers_.begin(); i != subscribers_.end(); ++i)
	{
		(*i)(args);
	}
}

bool CDefaultEvent::TryHappen(EventArg& args)
{
	for (auto i = subscribers_.begin(); i != subscribers_.end(); ++i)
	{
		if (!(*i)(args))
		{
			return false;
		}
	}
	return true;
}

void CDefaultEvent::Subscribe(bool (*func)(EventArg&))
{
	subscribers_.push_back(*func);
}

bool CDefaultEvent::Unsubscribe(bool (*func)(EventArg&))
{
	for (auto i = subscribers_.begin(); i != subscribers_.end(); ++i)
	{
		if (*i == func)
		{
			subscribers_.erase(i);
			return true;
		}
	}
	return false;
}