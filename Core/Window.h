#pragma once
#include "Windows.h"
#include <memory>
#include "Exceptions.h"
#include"Graphics.h"

// NIE DZIALA WSPARCIE DLA WIELU OKIEN, PROGRAM WYPIERDALA SIE PRZEZ WYWOLANIE DESTRUKTORA hehe xd

class Window {
public:
	Window(unsigned int width,unsigned int height) : m_Hwnd(nullptr), m_Height(height), m_Width(width) {}
	~Window() { DestroyWindow(m_Hwnd); }

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
	 void Show(int nCmdShow = SW_SHOWDEFAULT) const;
	 void SetWindowTitle(const std::wstring& title);

	 unsigned int GetWidth() const { return m_Width; }
	 unsigned int GetHeight() const { return m_Height; }
	 HWND GetNativeWindow() const { return m_Hwnd; }

	 //probably temp
	 Graphics& GetGraphics() { return *m_Graphics; }

protected:
	virtual LPCWSTR GetName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	unsigned int m_Width, m_Height;
	HWND m_Hwnd;

	std::unique_ptr<Graphics> m_Graphics;
};

class MainWindow : public Window {
public:
	MainWindow(unsigned int width, unsigned int height) :
		Window(width, height) {}
private:
	LPCWSTR GetName() const override { return L"New Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};
