#include "Window.h"
#include "WindowMessageString.h"

static WindowMessageString msg;

// INTERFACE
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Window* instance = nullptr;
	if (uMsg == WM_NCCREATE) {
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		instance = reinterpret_cast<Window*>(cs->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)instance);
		instance->m_hwnd = hwnd;
	}

	instance = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	if (instance) {
		return instance->HandleMessage(uMsg, wParam, lParam);
	}
	else {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

BOOL Window::Create(PCWSTR lpWindowName,
	DWORD dwStyle,
	DWORD dwExStyle,
	int x,
	int y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu) {

	WNDCLASSEX wndClass = {};
	wndClass.cbSize = sizeof(wndClass);
	wndClass.lpfnWndProc = Window::WindowProc;
	wndClass.hInstance = GetModuleHandle(nullptr);
	wndClass.lpszClassName = GetClassName();
	wndClass.style = CS_OWNDC;
	// Fill less important ones later on

	RegisterClassEx(&wndClass);

	m_hwnd = CreateWindowEx(
		dwExStyle,
		GetClassName(),
		lpWindowName,
		dwStyle,
		x, y, nWidth, nHeight,
		hWndParent,
		hMenu,
		GetModuleHandle(nullptr),
		this
	);

	return m_hwnd ? TRUE : FALSE;
}

void Window::Show(int nCmdShow) {
	ShowWindow(m_hwnd, nCmdShow);
}


// DERIVED CLASES
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	msg.PrintWindowMessage(uMsg);
	switch (uMsg) {
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(m_hwnd, &ps);
		break;
	}
	
	case WM_CLOSE:
		if (MessageBox(m_hwnd, L"Really wanna quit?", L"Message", MB_ICONWARNING | MB_OKCANCEL) == IDOK) {
			return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
		}
		else
			break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
	return TRUE;
}


