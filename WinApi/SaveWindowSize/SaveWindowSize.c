#include <windows.h>

#define WHERE_TO_SAVE TEXT("Software\\Programowanie pod Windows")

typedef struct win_size {
	DWORD width;
	DWORD height;
} win_size_t;

win_size_t getSize() {
	win_size_t w;

	DWORD dwType = REG_DWORD;
	DWORD dwSize = sizeof(DWORD);
	w.width = 512;
	w.height = 512;

	HKEY hKey;
	RegCreateKeyEx(HKEY_CURRENT_USER, WHERE_TO_SAVE, 0, NULL, 0, KEY_READ, NULL, &hKey, NULL);

	if (RegQueryValueEx(hKey, TEXT("width"), NULL, &dwType, (LPBYTE)&(w.width), &dwSize) != ERROR_SUCCESS) {
		w.width = 512;
	}

	if (RegQueryValueEx(hKey, TEXT("height"), NULL, &dwType, (LPBYTE)&(w.height), &dwSize) != ERROR_SUCCESS) {
		w.height = 512;
	}

	return w;
}

void setSize(HWND hwnd) {

	RECT rect;
	GetWindowRect(hwnd, &rect);

	DWORD width = rect.right - rect.left;
	DWORD height = rect.bottom - rect.top;

	HKEY hKey;
	RegCreateKeyEx(HKEY_CURRENT_USER, WHERE_TO_SAVE, 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL);

	RegSetValueEx(hKey, TEXT("width"), 0, REG_DWORD, (const BYTE*)&(width), sizeof(width));
	RegSetValueEx(hKey, TEXT("height"), 0, REG_DWORD, (const BYTE*)&(height), sizeof(height));

	RegCloseKey(hKey);
}


LRESULT CALLBACK WindowCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		setSize(hwnd);
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(ERROR_SUCCESS);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	win_size_t w = getSize();

	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	LPCWSTR my_lpszClassName = TEXT("myWindowClass");

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WindowCallback;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = my_lpszClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Window Registration Failed!"), TEXT("Error!"),
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		my_lpszClassName,
		TEXT("SaveWindowSize.c"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, w.width, w.height,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error!"),
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}
