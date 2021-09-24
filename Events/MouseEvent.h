#pragma once
#include "Event.h"

class MouseMovedEvent : public BaseEvent {
public:
	MouseMovedEvent(double _xpos, double _ypos) :
		xpos(_xpos), ypos(_ypos) {}

	double GetX() const { return xpos; }
	double GetY() const { return ypos; }
	static eventType GetStaticType() { return eventType::MOUSE_MOVED; }
	eventType getEventType() const override { return GetStaticType(); }

	EVENT_TYPE(MouseMoved);
private:
	double xpos, ypos;
};

class MousePressedEvent : public BaseEvent {
public:
	MousePressedEvent(int _button)
		: button(_button) { }

	int getButton() const { return button; }
	static eventType GetStaticType() { return eventType::MOUSE_PRESSED; }
	eventType getEventType() const override { return GetStaticType(); }
	EVENT_TYPE(MousePressed);
private:
	int button;
};

class MouseReleasedEvent : public BaseEvent {
public:
	MouseReleasedEvent(int _button)
		: button(_button) { }

	int getButton() const { return button; }
	static eventType GetStaticType() { return eventType::MOUSE_RELEASED; }
	eventType getEventType() const override { return GetStaticType(); }
	EVENT_TYPE(MouseReleased);
private:
	int button;
};
