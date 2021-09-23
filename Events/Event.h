#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <iostream>

enum class eventType {
	NONE = 0,
	MOUSE_PRESSED, MOUSE_RELEASED, MOUSE_MOVED,
	KEY_PRESSED, KEY_RELEASED,
	WINDOW_CLOSED, WINDOW_RESIZED
};

#define EVENT_TYPE(type) static const char* getStaticEventName() { return #type; }\
						 virtual const char* getEventName() const override { return getStaticEventName(); }

class BaseEvent {
public:
	virtual ~BaseEvent() = default;
	virtual eventType getEventType() const = 0;
	virtual const char* getEventName() const = 0;
private:
	bool handled = false; // potrzebne?
};

class EventDispatcher {
public:
	using EventCallbackFunction = std::function<void(BaseEvent&)>;

	template<typename T>
	void subscribe(const EventCallbackFunction& callbackFunction) {
		callbacks[T::getStaticEventName()].push_back(callbackFunction);
	}

	template<typename T>
	void dispatch(BaseEvent& event) { // const 
		const std::string eventName = event.getEventName();
		if (callbacks.find(eventName) == callbacks.end()) {
			std::cout << "Callback function is not set!\n";
			return;
		}
		else {
			// Call callback functions
			for (const auto& callback : callbacks.at(eventName))
				callback(event);
		}
	}

private: // string
	std::unordered_map<std::string, std::vector<EventCallbackFunction>> callbacks;
};