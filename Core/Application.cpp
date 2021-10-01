#include "Application.h"
#include"Keyboard.h"
#include"Mouse.h"
#include"MouseEvent.h"

#include<sstream>

Application::Application() : m_IsRunning(true) {
	m_Window = std::make_unique<MainWindow>(1000, 800);
	if (!m_Window->Create(L"New window", WS_OVERLAPPEDWINDOW))
		exit(-1);
	m_Window->Show();
}

void Application::ProcessMessages() {
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			m_IsRunning = false;
			return;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Application::Run() {
	while (m_IsRunning) {
		ProcessMessages();
		Testing();
		m_Window->GetGraphics().Clear();
		try {
			m_Window->GetGraphics().MakeTriangle();
			m_Window->GetGraphics().SwapBuffers();
		}
		catch (Exception& e) {
			GET_INFO(e);
		}		
	}
}

void Application::Testing() {
	if (Keyboard::s_Keyboard.KeyIsPressed(VK_SPACE)) {
		MessageBox(nullptr, L"Lecimy duur", L"ERROR", MB_OK);
	}

	if (Mouse::s_Mouse.LeftIsPressed()) {
		//OutputDebugStringA("MAM KLIKNIECIE\n");
	}

	while (!Mouse::s_Mouse.QueueIsEmpty()) {
		auto event = Mouse::s_Mouse.ReadEvent();
		if (event) {
			EventType type = (*event)->getEventType();
			switch (type) {
			case EventType::MouseMoved: {
				auto& e = static_cast<MouseMovedEvent&>(*(*event));
				std::wostringstream oss;
				oss << L"X: " << e.GetX() << L" Y:" << e.GetY();
				m_Window->SetWindowTitle(oss.str());
				break;
			}
			}
		}
	}
}