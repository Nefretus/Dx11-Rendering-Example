#include"Graphics.h"
#include"Exceptions.h"

Graphics::Graphics(HWND hwnd) {

	DXGI_SWAP_CHAIN_DESC sd = {};

	//Setting this to 0 will allow to check runtime parameters (ex. width)
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // can be rgba
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE; // on dal oba unspecified
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; 

	sd.SampleDesc.Count = 1; // should be 2 ?
	sd.SampleDesc.Quality = 0; // no anti-aliasing
		
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1; // 1 front ont back

	sd.OutputWindow = hwnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	THROW_IF_FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&m_SwapChain,
		&m_Device,
		nullptr,
		&m_Context
	));

	ID3D11Resource* backBuffer = nullptr;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&backBuffer));

	//D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	//rtvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_BUFFER; //or D3D11_RTV_DIMENSION_TEXTURE2D
	//rtvDesc.Buffer = { 0 }; // ?
	//...
	// for now i just passed nulptr for default values

	if (FAILED(m_Device->CreateRenderTargetView(
		backBuffer,
		nullptr,
		&m_TargetView
	))) {
		__debugbreak();
	}
	backBuffer->Release();
}

void Graphics::SwapBuffers() {
	m_SwapChain->Present( 1, 0);
}

void Graphics::Clear() {
	FLOAT colors[4] = { 0.1f, 0.2f, 0.3f, 1.0f };
	m_Context->ClearRenderTargetView(m_TargetView, colors);
}

Graphics::~Graphics() {
	if (m_Context)
		m_Context->Release();
	if (m_SwapChain)
		m_SwapChain->Release();
	if (m_Device)
		m_Device->Release();
	if (m_TargetView)
		m_TargetView->Release();
}
