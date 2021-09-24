#pragma once
#include"Event.h"
#include "Windows.h"

class KeyEvent : public BaseEvent {
public:
	int getKeyCode() { return key; }
protected:
	KeyEvent(int _key) : key(_key) {}
	int key;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int key) :
		KeyEvent(key) {}

	static eventType GetStaticType() { return eventType::KEY_PRESSED; }
	eventType getEventType() const override { return GetStaticType(); }

	EVENT_TYPE(KeyPressed);
private:
	// repeat count eventually 
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(int key) :
		KeyEvent(key) {}

	static eventType GetStaticType() { return eventType::KEY_RELEASED; }
	eventType getEventType() const override { return GetStaticType(); }
	EVENT_TYPE(KeyReleased);
};

class CharEvent : public BaseEvent {
public:
	CharEvent(WCHAR c) :
		character(c) {}

	static eventType GetStaticType() { return eventType::CHAR; }
	eventType getEventType() const override { return GetStaticType(); }

	WCHAR GetChar() const { return character; }
	EVENT_TYPE(CHAR);
private:
	WCHAR character;
};