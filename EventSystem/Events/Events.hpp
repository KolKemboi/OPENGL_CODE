#pragma once

enum class EventType
{
	KeyPress,
	KeyRelease,
	MouseMove,
	MouseScroll,
	MouseButtonPress,
	MouseButtonRelease,
	WindowResize,
	CameraMove
};

class Event
{
public:
	virtual ~Event() = default;
	virtual EventType getType() const = 0;
};

class EventDispatcher
{
public:
	EventDispatcher(Event& event) : m_Event(event){}
	
	template <typename T, typename F>
	bool dispatch(const F& func)
	{
		if (m_Event.getType() == T::getStaticType())
		{
			func(static_cast<T&>(m_Event));
			return true;
		}
		return false;
	}


private:
	Event& m_Event;
};