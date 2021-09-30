#include "Mouse.h"
#include "Keyboard.h"
#include "Window.h"
#include "WindowMessageString.h"
#include "resource.h"

static WindowMessageString msg;

// INTERFACE
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Window* instance = nullptr;
	if (uMsg == WM_NCCREATE) {
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		instance = reinterpret_cast<Window*>(cs->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)instance);
		instance->m_Hwnd = hwnd;
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
	wndClass.lpszClassName = GetName();
	wndClass.style = CS_OWNDC;

	try {
		wndClass.hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 32, 29, LR_DEFAULTCOLOR);
		wndClass.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 32, 29, LR_DEFAULTCOLOR);
		if(!wndClass.hIcon || !wndClass.hIconSm)
			throw Win32Exception(WFILE, __LINE__, GetLastError());
	}
	catch (Exception& e) {
		MessageBox(nullptr, e.Info().c_str(), L"ERROR", MB_OK);
	}
	// Fill less important ones later on

	RegisterClassEx(&wndClass);

	RECT wr;
	wr.left = 100;
	wr.right = m_Width + wr.left;
	wr.top = 100;
	wr.bottom = m_Height + wr.top;

	try {
		if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0) {
			throw Win32Exception(WFILE, __LINE__, GetLastError());
		}
	}
	catch (Exception& e) {
		MessageBox(nullptr, e.Info().c_str(), L"ERROR", MB_OK);
	}

	m_Hwnd = CreateWindowEx(
		dwExStyle,
		GetName(),
		lpWindowName,
		dwStyle,
		x, y, wr.right - wr.left, wr.bottom - wr.top,
		hWndParent,
		hMenu,
		GetModuleHandle(nullptr),
		this
	);

	if (m_Hwnd) {
		try {
			m_Graphics = std::make_unique<Graphics>(m_Hwnd);
		}
		catch (Exception& e) {
			MessageBox(nullptr, e.Info().c_str(), L"ERROR", MB_OK);
		}
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void Window::Show(int nCmdShow) const {
	ShowWindow(m_Hwnd, nCmdShow);
}


void Window::SetWindowTitle(const std::wstring& title) {
	SetWindowText(m_Hwnd, title.c_str());
	// ERROR CHECK
}

// DERIVED CLASES
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	msg.PrintWindowMessage(uMsg);
	switch (uMsg) {
	//case WM_PAINT: {
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(m_Hwnd, &ps);
	//	FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
	//	EndPaint(m_Hwnd, &ps);
	//	break;
	//}
	
	case WM_KILLFOCUS:
		Keyboard::s_Keyboard.ClearKeyStates();
		break;

	case WM_CLOSE:
		if (MessageBox(m_Hwnd, L"Really wanna quit?", L"Message", MB_ICONWARNING | MB_OKCANCEL) == IDOK) {
			return DefWindowProc(m_Hwnd, uMsg, wParam, lParam);
		}
		else
			break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;

	default:
		break;
	}
	Keyboard::s_Keyboard.WindoProc(this, uMsg, wParam, lParam);
	Mouse::s_Mouse.WindoProc(this, uMsg, wParam, lParam);
	return DefWindowProc(m_Hwnd, uMsg, wParam, lParam); // POSSIBLE BUG INVESTIGATE THIS
}


