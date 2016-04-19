#include <math.h>

#ifdef _WIN32
  #define DLL_EXPORT __declspec( dllexport )
#else
  #define DLL_EXPORT
#endif

int DLL_EXPORT isPrimeC (int n) {
	if (n <= 1 || n == 4) {
		return 0;
	}

	for (int i = 2; i < sqrt(n); i++) {
		if (n%i == 0) {
			return 0;
		}
	}

  return 1;
}
