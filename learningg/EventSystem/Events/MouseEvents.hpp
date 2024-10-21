#pragma once

#include "Events.hpp"

class MouseMovement : public Event
{
public:
	MouseMovement(double xPos, double yPos) : m_XPos(xPos), m_YPos(yPos) {}
	
	static EventType getStaticType() { return EventType::MouseMove; }
	EventType getType() const override { return getStaticType(); }
	
	double getX() const { return m_XPos; }
	double getY() const { return m_YPos; }


private:
	double m_XPos, m_YPos;
};

class MouseScrollEvent : public Event
{
public:
	MouseScrollEvent(double xOfffset, double yOffset) :
		m_XOffset(xOfffset), m_YOffset(yOffset) {}

	static EventType getStaticType() { return EventType::MouseScroll; }
	EventType getType() const override { return getStaticType(); }
	
	double getXOffset() const { return m_XOffset; }
	double getYOffset() const { return m_YOffset; }
	


private:
	double m_XOffset, m_YOffset;
};