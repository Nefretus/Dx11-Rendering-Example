#pragma once
#include"Windows.h"
#include<d3d11.h>
#include <wrl.h>

class Graphics {
public:
	Graphics(HWND hwnd);
	~Graphics() = default;
	Graphics& operator=(const Graphics&) = delete;
	Graphics(const Graphics&) = delete;

	void SwapBuffers();
	void Clear();
	void CreateConstantBuffer();

	void MakeTriangle();

private:
	float angle = 0.0f;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstBuffer = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Device> m_Device = nullptr;
	Microsoft::WRL::ComPtr <ID3D11DeviceContext> m_Context = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_TargetView = nullptr;
};