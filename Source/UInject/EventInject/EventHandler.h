#pragma once

template<class NameEvent>
class TPublicEvent final
{
private:
	NameEvent* _event;

public:
	explicit TPublicEvent(NameEvent* Event)
		: _event(Event)
	{
	}

	FDelegateHandle Add(typename NameEvent::FDelegate& Delegate)
	{
		return _event->Add(Delegate);
	}

	bool Remove(FDelegateHandle Handle)
	{
		return _event->Remove(Handle);
	}
};

template <class Owner, class NameEvent>
class TEventHandler
{
public:

	TPublicEvent<NameEvent> GetPublicEvent()
	{
		return _publicEvent;
	}
	
private:
	friend Owner;
	NameEvent Event;
	TPublicEvent<NameEvent> _publicEvent = TPublicEvent<NameEvent>(&Event);
};

