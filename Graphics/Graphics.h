#pragma once
#include"Windows.h"
#include<d3d11.h>

class Graphics {
public:
	Graphics(HWND hwnd);
	~Graphics();
	Graphics& operator=(const Graphics&) = delete;
	Graphics(const Graphics&) = delete;

	void SwapBuffers();
	void Clear();
private:
	IDXGISwapChain* m_SwapChain = nullptr;
	ID3D11Device* m_Device = nullptr;
	ID3D11DeviceContext* m_Context = nullptr;
	ID3D11RenderTargetView* m_TargetView = nullptr;
};