#pragma once
#include "Windows.h"
#include <memory>
#include "Exceptions.h"

// NIE DZIALA WSPARCIE DLA WIELU OKIEN, PROGRAM WYPIERDALA SIE PRZEZ WYWOLANIE DESTRUKTORA hehe xd

class Window {
public:
	Window() : m_hwnd(nullptr), height(0), width(0) {}
	~Window() { DestroyWindow(m_hwnd); }

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL Create(PCWSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExStyle = 0,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU hMenu = 0);

	 // Argument controls how Window is to be shown
	 void Show(int nCmdShow);

protected:
	virtual LPCWSTR GetClassName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	unsigned int width, height;
	HWND m_hwnd;
};

class MainWindow : public Window {
private:
	LPCWSTR GetClassName() const override { return L"New Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};
