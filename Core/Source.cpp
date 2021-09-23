#include "Window.h"
#include <shobjidl.h> 

//#define DialogBoxExample
//#define ErrorThrowExample
#define MyWindowTest

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

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

#ifdef ErrorThrowExample
	try {
		throw WindowException(WFILE, __LINE__, ERROR_ACCESS_DENIED);
	}
	catch (Exception& e) {
		MessageBox(nullptr, e.Info().c_str(), L"ERROR", MB_OK);
	}
#endif

	return 0;
#endif
}
