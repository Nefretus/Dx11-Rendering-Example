#include "MouseEvent.h"
#include "Mouse.h" // zamiana tego miejscami wypierdala bledy ????

Mouse Mouse::s_Mouse;

Mouse::Mouse() :
	m_LeftButtonPressed(false), m_RightButtonPressed(false),
	m_Xpos(0), m_Ypos(0), m_MouseIsInWindow(false)
{}

void Mouse::WindoProc(Window* window, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_LBUTTONDOWN: {
		OnLeftPressed(MK_LBUTTON);
		break;
	}
	case WM_RBUTTONDOWN: {
		OnRightPressed(MK_RBUTTON);
		break;
	}
	case WM_LBUTTONUP: {
		OnLeftReleased(MK_LBUTTON);
		break;
	}
	case WM_RBUTTONUP: {
		OnRightReleased(MK_RBUTTON);
		break;
	}
	case WM_MOUSEMOVE: {
		POINTS point = MAKEPOINTS(lParam);
		if ((point.x >= 0 && point.x < window->GetWidth()) && (point.y >= 0 && point.y < window->GetHeight())) {
			OnMouseMove(point.x, point.y);
			HWND hwnd = window->GetNativeWindow();
			if (!m_MouseIsInWindow) { 
				SetCapture(hwnd);
				m_MouseIsInWindow = true;
			}
			break;
		}
		else {
			if (m_LeftButtonPressed || m_RightButtonPressed) {
				OnMouseMove(point.x, point.y);
			}
			else {
				ReleaseCapture();
				m_MouseIsInWindow = false;
			}
		}
		break;
	}
	default:
		return;
	}
}

std::pair<int, int> Mouse::GetMousePositions() const {
	return std::make_pair(m_Xpos, m_Ypos);
}

int Mouse::GetXpos() const {
	auto [x, y] = GetMousePositions();
	return x;
}

int Mouse::GetYPos() const {
	auto [x, y] = GetMousePositions();
	return y;
}

bool Mouse::LeftIsPressed() const {
	return m_LeftButtonPressed;
}

bool Mouse::RightIsPressed() const {
	return m_RightButtonPressed;
}

void Mouse::OnLeftPressed(int button) {
	m_EventQueue.push(std::move(std::make_unique<MousePressedEvent>(button)));
	m_LeftButtonPressed = true;
	TrimBuffer(m_EventQueue);
}

void Mouse::OnRightPressed(int button) {
	m_EventQueue.push(std::move(std::make_unique<MousePressedEvent>(button)));
	m_RightButtonPressed = true;
	TrimBuffer(m_EventQueue);
}

void Mouse::OnRightReleased(int button) {
	m_EventQueue.push(std::move(std::make_unique<MouseReleasedEvent>(button)));
	m_RightButtonPressed = false;
	TrimBuffer(m_EventQueue);
}


void Mouse::OnLeftReleased(int button) {
	m_EventQueue.push(std::move(std::make_unique<MouseReleasedEvent>(button)));
	m_LeftButtonPressed = false;
	TrimBuffer(m_EventQueue);
}

void Mouse::OnMouseMove(int xpos, int ypos) {
	m_EventQueue.push(std::move(std::make_unique<MouseMovedEvent>(xpos, ypos)));
	m_Xpos = xpos;
	m_Ypos = ypos;
	TrimBuffer(m_EventQueue);
}

void Mouse::OnWheelUp(int x, int y) {
	return;
}

void Mouse::OnWheelDown(int x, int y) {
	return;
}
