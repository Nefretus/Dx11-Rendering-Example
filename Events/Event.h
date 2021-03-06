#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <iostream>

enum class EventType {
	None = 0,
	MousePressed, MouseReleased, MouseMoved,
	KeyPressed, KeyReleased, Char
};

#define EVENT_TYPE(type) static const char* getStaticEventName() { return #type; }\
						 virtual const char* getEventName() const override { return getStaticEventName(); }

class BaseEvent {
public:
	virtual ~BaseEvent() = default;
	virtual EventType getEventType() const = 0;
	virtual const char* getEventName() const = 0;
private:
	bool handled = false; 
};

class EventDispatcher {
public:
	using EventCallbackFunction = std::function<void(BaseEvent&)>;

	template<typename T>
	void subscribe(const EventCallbackFunction& callbackFunction) {
		callbacks[T::getStaticEventName()].push_back(callbackFunction);
	}

	template<typename T>
	void dispatch(BaseEvent& event) { 
		const std::string eventName = event.getEventName();
		if (callbacks.find(eventName) == callbacks.end()) {
			std::cout << "Callback function is not set!\n";
			return;
		}
		else {
			for (const auto& callback : callbacks.at(eventName))
				callback(event);
		}
	}

private: 
	std::unordered_map<std::string, std::vector<EventCallbackFunction>> callbacks;
};