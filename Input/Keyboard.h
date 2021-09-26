#pragma once
#include "InputDevice.h"
#include "Windows.h"
#include <bitset>

class Keyboard : public InputDevice {
public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;

	static Keyboard s_Keyboard;

	void WindoProc(/*Wundow* inst*/UINT uMsg, WPARAM wParam, LPARAM lParam);

	bool KeyIsPressed(int keycode) const;
	void ClearKeyStates();
	// char?

private:
	void OnKeyPressed(int keyCode);
	void OnKeyReleased(int keyCode);
	void OnChar(WCHAR character);

	static constexpr unsigned int m_MaxKeyCodes = 256u;
	std::bitset<m_MaxKeyCodes> m_KeyStates;
};