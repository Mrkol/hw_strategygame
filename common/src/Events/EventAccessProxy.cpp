#include "Events/EventAccessProxy.hpp"
#include "UniversalException.hpp"

namespace Common { namespace Events 
{
	EventAccessProxy::EventAccessProxy(IEvent& controlled)
		: controlled_(controlled)
	{

	}

	void EventAccessProxy::Trigger(EventArgs& args)
	{
		throw UniversalException() << "Attempted to trigger an event through a proxy.";
	}

	void EventAccessProxy::Subscribe(const std::string& id, Callback callback)
	{
		controlled_.Subscribe(id, callback);
	}

	bool EventAccessProxy::Unsubscribe(const std::string& id)
	{
		return controlled_.Unsubscribe(id);
	}
} }
