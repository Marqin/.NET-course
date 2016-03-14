#include <windows.h>

#include <stdio.h>

#define CHAIRS 5
#define MAX_CUSTOMERS 1000

typedef struct barbershop_struct {
	DWORD customers;
	HANDLE mutex;
	HANDLE barber;
	HANDLE customer;
} barbershop_t;

barbershop_t* new_barbershop() {

	barbershop_t* barbershop = HeapAlloc(GetProcessHeap(), 0, sizeof(barbershop_t));
	SecureZeroMemory(barbershop, sizeof(barbershop_t));

	barbershop->customers = 0;
	
	barbershop->mutex = CreateSemaphore(NULL, 1, LONG_MAX, TEXT("mutex"));
	if (barbershop->mutex == NULL) {
		printf("MTX err: %d\n", GetLastError());
	}
	barbershop->barber = CreateSemaphore(NULL, 0, LONG_MAX, TEXT("barber"));
	if (barbershop->mutex == NULL) {
		printf("BRB err: %d\n", GetLastError());
	}
	barbershop->customer = CreateSemaphore(NULL, 0, LONG_MAX, TEXT("customer"));
	if (barbershop->mutex == NULL) {
		printf("CST err: %d\n", GetLastError());
	}

	return barbershop;
}

DWORD WINAPI BarberThread(LPVOID ptr) {

	barbershop_t* barbershop = ptr;
	while(TRUE) {
		WaitForSingleObject(barbershop->customer, INFINITE);  // sleep
		ReleaseSemaphore(barbershop->barber, 1, NULL);  // start cutting
		printf("Cutting Hair!\n");
	}
	return EXIT_SUCCESS;
}

DWORD WINAPI CustomerThread(LPVOID ptr) {
	barbershop_t* barbershop = ptr;

	// only one tread can access barbershop->customers in the same moment
	WaitForSingleObject(barbershop->mutex, INFINITE);
		if (barbershop->customers > CHAIRS) {
			ReleaseSemaphore(barbershop->mutex, 1, NULL);
			return EXIT_FAILURE;  // barbershop is full
		}
		barbershop->customers++;
	ReleaseSemaphore(barbershop->mutex, 1, NULL);

	ReleaseSemaphore(barbershop->customer, 1, NULL);  // signal barber that we entered
	WaitForSingleObject(barbershop->barber, INFINITE);  // wait for barber
	printf("My hair are getting cut!\n");


	// only one tread can access barbershop->customers in the same moment
	WaitForSingleObject(barbershop->mutex, INFINITE);
	barbershop->customers--;
	ReleaseSemaphore(barbershop->mutex, 1, NULL);

	return EXIT_SUCCESS;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	// we need console for stdout
	AllocConsole();
	FILE *nothing;
	freopen_s(&nothing, "CONOUT$", "wb", stdout);


	barbershop_t* barbershop = new_barbershop();
	DWORD went = 0;

	DWORD customerID[MAX_CUSTOMERS + 1];
	HANDLE customer[MAX_CUSTOMERS +1];

	DWORD BarberID;
	HANDLE barber = CreateThread(NULL, 0, BarberThread, barbershop, 0, &BarberID);
	
	while ( went < MAX_CUSTOMERS) {
		DWORD nr = went + rand()%(CHAIRS+2);
		for (; went < nr && went < MAX_CUSTOMERS; went++) {
			customer[went] = CreateThread(NULL, 0, CustomerThread, barbershop, 0, &(customerID[went]));
		}
		Sleep(rand()%1000);
	}

	WaitForMultipleObjects(MAX_CUSTOMERS, customer, TRUE, INFINITE);
	printf("\n\nTests finished.\n\n");
	TerminateThread(barber, EXIT_SUCCESS);

	// for some reason getchar();s are not working :-(
	system("PAUSE");

	return 0;
}