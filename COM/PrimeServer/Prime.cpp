// Prime.cpp : Implementation of CPrime

#include "stdafx.h"
#include "Prime.h"


// CPrime



STDMETHODIMP CPrime::IsPrime(int n, int* isPrime)
{

	if (n <= 1 || n == 4) {
		*isPrime = 0;
		return S_OK;
	}

	*isPrime = 42;

	for (int i = 2; i < sqrt(n); i++) {
		if (n%i == 0) {
			*isPrime = 0;
		}
	}

	return S_OK;
}
