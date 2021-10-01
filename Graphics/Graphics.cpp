#include"Graphics.h"
#include"Exceptions.h"
#include<d3dcompiler.h>

#pragma comment(lib, "D3DCompiler.lib")

Graphics::Graphics(HWND hwnd) {

	unsigned int creationFlags = 0;

#if defined(_DEBUG)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

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
		creationFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&m_SwapChain,
		&m_Device,
		nullptr,
		&m_Context
	));

	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer = nullptr;

	THROW_IF_FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer));

	//D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	//rtvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_BUFFER; //or D3D11_RTV_DIMENSION_TEXTURE2D
	//rtvDesc.Buffer = { 0 }; // ?
	//...
	// for now i just passed nulptr for default values

	THROW_IF_FAILED(m_Device->CreateRenderTargetView(
		backBuffer.Get(),
		nullptr,
		&m_TargetView
	));
}

void Graphics::SwapBuffers() {
	THROW_IF_FAILED(m_SwapChain->Present( 1, 0));
}

void Graphics::Clear() {
	FLOAT colors[4] = { 0.1f, 0.2f, 0.3f, 1.0f };
	m_Context->ClearRenderTargetView(m_TargetView.Get(), colors);
}

void Graphics::MakeTriangle() {
	
	float verticies[] = {
		-1.0f, 0.0f,
		 1.0f, 0.0f,
		 0.0f, 1.0f
	};

	//Vertex Buffer description
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth =  sizeof(verticies);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0; //	
	desc.MiscFlags = 0;
	desc.StructureByteStride = 2 * sizeof(float);

	// Load data
	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = verticies; 
	
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

	const UINT stride = desc.StructureByteStride;
	const UINT offest = 0;
	THROW_IF_FAILED(m_Device->CreateBuffer(&desc, &data, &vertexBuffer));
    m_Context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offest); //& ???
	
	//set vertex buffer layout
	D3D11_INPUT_ELEMENT_DESC elementDesc = {};
	//elementDesc.


	Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
	//m_Device->CreateInputLayout( , 1, )


	// VERTEX SHADER
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vs;
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	THROW_IF_FAILED(D3DReadFileToBlob(L"VertexShader.cso", &blob));
	THROW_IF_FAILED(m_Device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, vs.GetAddressOf())); //there can e & i guess
	m_Context->VSSetShader(vs.Get(), nullptr, 0);

	// Pixel shader
	THROW_IF_FAILED(D3DReadFileToBlob(L"VertexShader.cso", &blob));
	Microsoft::WRL::ComPtr<ID3D11PixelShader> ps;
	m_Device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, ps.GetAddressOf());
	m_Context->PSSetShader(ps.Get(), nullptr, 0);

	//setting render targets
	m_Context->OMSetRenderTargets(1, m_TargetView.GetAddressOf(), nullptr);

	// configure viewport, we dont need to split the screen just make one viewport
	D3D11_VIEWPORT vp = {};
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = 1000;     // here we propably would need to have access to window coords
	vp.Height = 800;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	m_Context->RSSetViewports(1, &vp);

	// set primitive topology
	m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Context->Draw(3, 0);
}
