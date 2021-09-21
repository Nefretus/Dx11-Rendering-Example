#include "Window.h"
#include <shobjidl.h> 

//#define DialogBoxExample
#define MyWindowTest

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	/*//Create a class
	const wchar_t className[] = L"test";
	WNDCLASS myClass = {};
	myClass.lpfnWndProc = WindowProc;
	myClass.hInstance = hInstance;
	myClass.lpszClassName = className;
	
	myClass.style = CS_OWNDC;
	myClass.lpszMenuName = NULL;

	//Register it
	RegisterClass(&myClass);

	StateInfo* pState = new (std::nothrow) StateInfo;

	if (pState == NULL)
	{
		return 0;
	}

	//Create instance
	HWND hwnd = CreateWindowEx(
		0,
		className,
		L"Thats a window name",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		pState
	);

	if (!hwnd)
		return -1;

	ShowWindow(hwnd, nCmdShow);
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//while (true);

	//delete pState;*/

	HRESULT result = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

#ifdef DialogBoxExample
	if (SUCCEEDED(result)) {
		IFileOpenDialog* fileOpen;
		
		result = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog,
			reinterpret_cast<void**>(&fileOpen));

		if (SUCCEEDED(result)) {
			result = fileOpen->Show(NULL);
			if (SUCCEEDED(result)) {
				IShellItem* item;
				result = fileOpen->GetResult(&item);
				if (SUCCEEDED(result)) {
					PWSTR filePath;
					item->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

					MessageBoxW(NULL, filePath, L"File Path", MB_OK);
					CoTaskMemFree(filePath);
					item->Release();
				}
			}
			fileOpen->Release();
		}
		CoUninitialize();
		return 0;
	}

	else
		return -1;
#endif

#ifdef MyWindowTest
	MainWindow window;
	window.Create(L"New window", WS_OVERLAPPEDWINDOW);
	window.Show(nCmdShow);
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CoUninitialize();
	return 0;
#endif
}
