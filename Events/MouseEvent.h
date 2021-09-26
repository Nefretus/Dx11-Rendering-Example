#pragma once
#include "Event.h"

class MouseMovedEvent : public BaseEvent {
public:
	MouseMovedEvent(int _xpos, int _ypos) :
		xpos(_xpos), ypos(_ypos) {}

	int GetX() const { return xpos; }
	int GetY() const { return ypos; }
	static EventType GetStaticType() { return EventType::MouseMoved; }
	EventType getEventType() const override { return GetStaticType(); }

	EVENT_TYPE(MouseMoved);
private:
	int xpos, ypos;
};

class MousePressedEvent : public BaseEvent {
public:
	MousePressedEvent(int _button)
		: button(_button) { }

	int getButton() const { return button; }
	static EventType GetStaticType() { return EventType::MousePressed; }
	EventType getEventType() const override { return GetStaticType(); }
	EVENT_TYPE(MousePressed);
private:
	int button;
};

class MouseReleasedEvent : public BaseEvent {
public:
	MouseReleasedEvent(int _button)
		: button(_button) { }

	int getButton() const { return button; }
	static EventType GetStaticType() { return EventType::MouseReleased; }
	EventType getEventType() const override { return GetStaticType(); }
	EVENT_TYPE(MouseReleased);
private:
	int button;
};
