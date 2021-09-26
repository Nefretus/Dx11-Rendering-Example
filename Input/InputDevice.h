#pragma once
#include <queue>
#include <memory>
#include <optional>
#include "Event.h"

class InputDevice {
public:
	template<typename T>
	void TrimBuffer(std::queue<T>& queue) {
		while (queue.size() > m_BufferSize) {
			queue.pop();
		}
		
	}

	void ClearQueue() { m_EventQueue = std::queue<std::unique_ptr<BaseEvent>>(); }

	bool QueueIsEmpty() { return m_EventQueue.empty(); }

	std::optional<std::unique_ptr<BaseEvent>> ReadEvent() {
		if (!m_EventQueue.empty()) {
			std::unique_ptr<BaseEvent> e = std::move(m_EventQueue.front());
			m_EventQueue.pop();
			return e;
		}
		return std::nullopt;
	}

public: // change to protected!!!
	const unsigned int m_BufferSize = 30u;
	std::queue<std::unique_ptr<BaseEvent>> m_EventQueue;
};
