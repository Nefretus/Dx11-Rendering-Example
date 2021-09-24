#pragma once
#include <queue>
#include <memory>
#include "Event.h"

class InputDevice {
public:
	template<typename T>
	void TrimBuffer(std::queue<T>& queue) {
		while (queue.size() > m_BufferSize) {
			queue.pop();
		}
	}

	void ClearQueue() { m_EventQueue = std::queue< std::unique_ptr<BaseEvent>>(); }
protected:
	const unsigned int m_BufferSize = 30u;
	std::queue<std::unique_ptr<BaseEvent>> m_EventQueue;
};