#pragma once
#include "InputDevice.h"
#include "Window.h"

class Mouse: public InputDevice {
public:
	Mouse();
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	static Mouse s_Mouse;

	void WindoProc(Window* inst, UINT uMsg, WPARAM wParam, LPARAM lParam);

	std::pair<int, int> GetMousePositions() const;
	int GetXpos() const;
	int GetYPos() const;
	bool LeftIsPressed() const;
	bool RightIsPressed() const;
	//bool IsMouseInWindow() const;
	// I need to support mouse scrolling

private:
	void OnLeftPressed(int button);
	void OnRightPressed(int button);
	void OnLeftReleased(int button);
	void OnRightReleased(int button);
	void OnMouseMove(int xpos, int ypos);
	// TODO
	void OnWheelUp(int x, int y) ;
	void OnWheelDown(int x, int y) ;

	bool m_LeftButtonPressed, m_RightButtonPressed;
	int m_Xpos, m_Ypos;
	bool m_MouseIsInWindow;
};
