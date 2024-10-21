#pragma once

#include "Events.hpp"

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(int width, int height) :
		m_Width(width), m_Height(height) {}

	static EventType getStaticType() { return EventType::WindowResize; }
	EventType getType() const override { return getStaticType(); }
	
	int getWidth() const { return m_Width; }
	int getHeight() const { return m_Height; }

private:
	int m_Width, m_Height;
};