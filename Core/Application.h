#pragma once
#include<memory>
#include"Window.h"

class Window;
class Application {
public:
	Application();
	void Run();
private:
	void ProcessMessages();
	void Testing();

	std::unique_ptr<Window> m_Window;
	bool m_IsRunning;
};

