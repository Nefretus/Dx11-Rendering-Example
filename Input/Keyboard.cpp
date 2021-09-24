#include"Keyboard.h"
#include "KeyboardEvent.h"

Keyboard Keyboard::s_Keyboard;

void Keyboard::WindoProc(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CHAR: {
		OnChar(static_cast<WCHAR>(wParam));
		break;
	}
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN: {
		OnKeyPressed(static_cast<int>(wParam));
		break;
	}
	case WM_KEYUP:
	case WM_SYSKEYUP: {
		OnKeyReleased(static_cast<int>(wParam));
		break;
	}
	default:
		return;
	}
}

bool Keyboard::KeyIsPressed(int keycode) const {
	return m_KeyStates[keycode];
}


void Keyboard::OnKeyPressed(int keyCode) { // unsigned char???
	m_KeyStates[keyCode] = true;
	m_EventQueue.push(std::move(std::make_unique<KeyPressedEvent>(keyCode)));
	TrimBuffer(m_EventQueue);
}

void Keyboard::OnKeyReleased(int keyCode) {
	m_KeyStates[keyCode] = false;
	m_EventQueue.push(std::move(std::make_unique<KeyReleasedEvent>(keyCode)));
	TrimBuffer(m_EventQueue);
}

void Keyboard::OnChar(WCHAR character) {
	m_EventQueue.push(std::move(std::make_unique<CharEvent>(character)));
	TrimBuffer(m_EventQueue);
}
