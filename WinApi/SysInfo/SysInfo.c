//#define _WIN32_WINNT  0x0501

#include <windows.h>
#include <stdio.h>

#include <tchar.h>  // _tprintf

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winspool.lib")

BOOL getDWORDFromRegistry(LPSTR path, LPSTR name, PDWORD dw) {
	DWORD type = REG_DWORD;
	DWORD size = sizeof(*dw);

	HKEY hKey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &hKey);
	if (RegQueryValueEx(hKey, name, NULL, &type, (LPBYTE)(dw), &size) != ERROR_SUCCESS) {
		return FALSE;
	}
	RegCloseKey(hKey);
	return TRUE;
}

LPSTR getREG_SZFromRegistry(LPSTR path, LPSTR name) {
	LPSTR str;
	DWORD szType = REG_SZ;
	DWORD strSize = 0;

	HKEY hKey;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &hKey);

	// get str length
	if (RegQueryValueEx(hKey, name, NULL, &szType, NULL, &strSize) != ERROR_SUCCESS) {
		return NULL;
	}

	strSize += 2;
	str = HeapAlloc(GetProcessHeap(), 0, strSize);
	SecureZeroMemory(str, strSize);

	if (RegQueryValueEx(hKey, name, NULL, &szType, (LPBYTE)(str), &strSize) != ERROR_SUCCESS) {
		free(str);
		return NULL;
	}
	RegCloseKey(hKey);
	return str;
}

void printCPU() {
	LPSTR model = getREG_SZFromRegistry(TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), TEXT("ProcessorNameString"));
	DWORD speed = 0;
	
	if (!getDWORDFromRegistry(TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), TEXT("~MHz"), &speed)) {
		speed = 0;
	}

	printf("CPU Model: ");
	if (model == NULL) {
		printf("(none)\n");
	}
	else {
		_tprintf(TEXT("%s\n"), model);
	}

	printf("CPU Speed: ");
	if (speed == 0) {
		printf("(none)\n");
	}
	else {
		_tprintf(TEXT("%d MHz\n"), speed);
	}
}


void printMem() {
	MEMORYSTATUSEX mem;
	ZeroMemory(&mem, sizeof(MEMORYSTATUSEX));
	mem.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&mem);
	printf("Memory: %lld/%lld (%lld%%)\n", mem.ullAvailPhys, mem.ullTotalPhys, (100 * mem.ullAvailPhys) / mem.ullTotalPhys);
}

void printOS() {
	OSVERSIONINFOEX os;
	ZeroMemory(&os, sizeof(OSVERSIONINFOEX));
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx(&os);
	printf("Windows: %d.%d.%d %s\n", os.dwMajorVersion, os.dwMinorVersion, os.dwBuildNumber, os.szCSDVersion);
}

void printUser() {
	TCHAR user[1024] = { 0 };
	DWORD usize = sizeof(user);
	TCHAR name[1024] = { 0 };
	DWORD nsize = sizeof(name);
	GetUserName(user, &usize);
	GetComputerName(name, &nsize);
	_tprintf(TEXT("User: %s@%s\n"), user, name);
}

void printScreen() {
	HDC hdc = GetDC(NULL);
	int colorDepth = GetDeviceCaps(hdc, BITSPIXEL) * GetDeviceCaps(hdc, PLANES);
	int width = GetDeviceCaps(hdc, HORZRES);
	int height = GetDeviceCaps(hdc, VERTRES);
	printf("Screen: %dx%d (%d-bit)\n", width, height, colorDepth);
}

void printPrinters() {
	PRINTER_INFO_1 pinfo[1024];
	DWORD flag = PRINTER_ENUM_LOCAL | PRINTER_ENUM_SHARED | PRINTER_ENUM_NETWORK;
	DWORD num = 0;
	DWORD n;
	EnumPrinters(flag, NULL, 1, (PBYTE)pinfo, sizeof(pinfo), &n, &num);
	printf("Printers: ");
	if (!num) {
		printf("(none)\n");
	}
	else {
		for (DWORD i = 0; i < num && i < 1024; i++) {
			_tprintf(TEXT("%s"), pinfo[i].pName);
			if (i < num - 1 && i < 1023) {
				printf(", ");
			}
		}
		printf("\n");
	}
}

void printNET() {

	LPSTR str = getREG_SZFromRegistry(TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP"), TEXT("Version"));

	if ( str == NULL ) {
		str = getREG_SZFromRegistry(TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full"), TEXT("Version"));
	}

	printf(".NET Framework: ");
	if (str == NULL) {
		printf("(none)\n");
	}
	else {
		_tprintf(TEXT("%s\n"), str);
	}

}

void printIE() {
	LPSTR str = getREG_SZFromRegistry(TEXT("SOFTWARE\\Microsoft\\Internet Explorer"), TEXT("Version"));

	printf("Internet Explorer: ");
	if (str == NULL) {
		printf("(none)\n");
	}
	else {
		_tprintf(TEXT("%s\n"), str);
	}
}

void printMSOFFICE() {

	int num = 0;

	for (int i = 7; i <= 16; i++) {
		if (i == 13) {
			continue;
		}

		TCHAR str[1024] = { 0 };
		TCHAR buf[10] = { 0 };

		//Wow6432Node po soft ew
		lstrcat(str, TEXT("SOFTWARE\\Microsoft\\Office\\"));		
		_itot_s(i, buf, 8, 10);

		lstrcat(str, buf);

		lstrcat(str, TEXT(".0\\Common\\InstallRoot"));


		if (getREG_SZFromRegistry(str, TEXT("Path")) != NULL) {
			num = i;
			break;
		}

	}

	switch (num) {
	case 7:
		puts("MSOFFICE: 97");
		break;
	case 8:
		puts("MSOFFICE: 97");
		break;
	case 9:
		puts("MSOFFICE: 97");
		break;
	case 10:
		puts("MSOFFICE: 97");
		break;
	case 11:
		puts("MSOFFICE: 97");
		break;
	case 12:
		puts("MSOFFICE: 97");
		break;
	case 14:
		puts("MSOFFICE: 97");
		break;
	case 15:
		puts("MSOFFICE: 97");
		break;
	case 16:
		puts("MSOFFICE: 97");
		break;
	default:
		puts("MSOFFICE: (none)");
		break;
	}

}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {


	// we need console for stdout
	AllocConsole();
	FILE *nothing;
	freopen_s(&nothing, "CONOUT$", "wb", stdout);

	printCPU();

	printMem();

	printOS();

	printUser();

	// -lgdi32
	printScreen();

	// -lwinspool
	printPrinters();

	printNET();

	printIE();

	printMSOFFICE();

	// for some reason getchar();s are not working :-(
	system("PAUSE");

	return 0;
}
