#include "Events/event.hpp"
#include <memory>

namespace Common { namespace Events
{
	void Event::Trigger(EventArgs& args)
	{
		for (auto i = subscribers_.begin(); i != subscribers_.end(); ++i)
		{
			i->second(args);
		}
	}

	void Event::Subscribe(const std::string& id, Callback callback)
	{
		//TODO: consider the behaviour when there's a function with such ID already
		subscribers_[id] = callback;
	}

	bool Event::Unsubscribe(const std::string& id)
	{
		auto iter = subscribers_.find(id);
		if (iter == subscribers_.end())
			return false;

		subscribers_.erase(iter);
		return true;
	}
} }