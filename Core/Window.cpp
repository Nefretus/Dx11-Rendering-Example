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
	wndClass.lpszClassName = GetClassName();
	wndClass.style = CS_OWNDC;

	try {
		wndClass.hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 32, 29, LR_DEFAULTCOLOR);
		wndClass.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 32, 29, LR_DEFAULTCOLOR);
		if(!wndClass.hIcon || !wndClass.hIconSm)
			throw WindowException(WFILE, __LINE__, GetLastError());	
	}
	catch (Exception& e) {
		MessageBox(nullptr, e.Info().c_str(), L"ERROR", MB_OK);
	}
	// Fill less important ones later on

	RegisterClassEx(&wndClass);

	m_Hwnd = CreateWindowEx(
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

	return m_Hwnd ? TRUE : FALSE;
}

void Window::Show(int nCmdShow) {
	ShowWindow(m_Hwnd, nCmdShow);
}


// DERIVED CLASES
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	msg.PrintWindowMessage(uMsg);
	switch (uMsg) {
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_Hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(m_Hwnd, &ps);
		break;
	}
	
	case WM_CLOSE:
		if (MessageBox(m_Hwnd, L"Really wanna quit?", L"Message", MB_ICONWARNING | MB_OKCANCEL) == IDOK) {
			return DefWindowProc(m_Hwnd, uMsg, wParam, lParam);
		}
		else
			break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	// GLOBAL VARIABLES
	//if (uMsg == WM_CHAR)
		//_debugbreak();
	Keyboard::s_Keyboard.WindoProc(uMsg, wParam, lParam);
	//Mouse
	return DefWindowProc(m_Hwnd, uMsg, wParam, lParam);
}


