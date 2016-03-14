#include <windows.h>

#include <shlobj.h>

#include <stdio.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	TCHAR desktopDir[MAX_PATH+2] = { 0 };
	SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, 0, 0, desktopDir);

	LPWSTR filePath = lstrcat(desktopDir, TEXT("/sysTime.txt"));

	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);

	TCHAR date[1024] = { 0 };

	wsprintf(date, TEXT("%04d-%02d-%02d %02d:%02d:%02d\n"), sysTime.wYear, sysTime.wMonth,
		sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);


	HANDLE hFile = CreateFile(filePath, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBox(0, TEXT("Could not create/open a file"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return 0;
	}

	DWORD dwWritten;
	WriteFile(hFile, date, lstrlen(date)*sizeof(TCHAR), &dwWritten, NULL);

	if (dwWritten != (lstrlen(date)*sizeof(TCHAR))) {
		MessageBox(0, TEXT("File was not written properly!"), TEXT("Error"), MB_OK | MB_ICONERROR);
	}

	CloseHandle(hFile);

	ShellExecute(0, TEXT("print"), filePath, NULL, NULL, SW_NORMAL);

	return 0;
}
