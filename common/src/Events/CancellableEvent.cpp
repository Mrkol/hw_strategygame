#include "Events/CancellableEvent.hpp"

namespace Common { namespace Events
{
	void CancellableEventArgs::CancelEvent()
	{
		if (status_ == EventStatus::Active)
		{
			status_ = EventStatus::Cancelled;
		}
	}

	void CancellableEventArgs::ReactivateEvent()
	{
		if (status_ == EventStatus::Cancelled)
		{
			status_ = EventStatus::Active;
		}
	}

	void CancellableEventArgs::TerminateEvent()
	{
		status_ = EventStatus::Terminated;
	}

	EventStatus CancellableEventArgs::GetEventStatus()
	{
		return status_;
	}

	void CancellableEvent::Trigger(EventArgs& args)
	{
		CancellableEventArgs& casted = static_cast<CancellableEventArgs&>(args);

		for (auto i = subscribers_.begin(); i != subscribers_.end(); ++i)
		{
			i->second(casted);
			if (casted.GetEventStatus() == EventStatus::Terminated)
				break;
		}
	}
} }
