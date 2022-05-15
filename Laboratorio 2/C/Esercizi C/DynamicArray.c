#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"

//I/O
int* ReadArray(int n)
{
	int* arr = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	return arr;
}

void PrintArrayline(int* arr, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
}

void PrintArray(int* arr, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d\n", arr[i]);
}




//int CheckIfProperty(int* n1, int n2, int(*f)(const void*, const void*))
//{
//	//CheckIfOrdered(arr, n, OrdineCrescente);
//		if (f(&arr[i], &arr[i + 1]) == 1)
//			return 0;
//	return 1;
//}



//PROPERTY CHECK
int CheckIfOrdered(int* arr, int n, int(*f)(const void*, const void*))
{
	//CheckIfOrdered(arr, n, OrdineCrescente);
	for (int i = 0; i < n - 1; i++)
		if (f(&arr[i], &arr[i+1]) == 1)
			return 0;
	return 1;
}



//ORDER FUNCTION

int OrdineCrescente(const void* n1, const void* n2)
{
	//qsort(arr, n , sizeof(int*), OrdineCrescente);
	int a = *((int*)n1);
	int b = *((int*)n2);


	if (a > b)
		return 1;
	else if (a == b)
		return 0;
	else
		return -1;
}
int OrdineDecrescente(const void* n1, const void* n2)
{
	//qsort(arr, n , sizeof(int*), OrdineDecrescente);
	int a = *((int*)n1);
	int b = *((int*)n2);


	if (a < b)
		return 1;
	else if (a == b)
		return 0;
	else
		return -1;
}

//UTILITY
void Swap(int* a, int* b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

int ContaPari(int* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] % 2 != 0)
			return i;
	}
	return 0;
}


//ARRAY ALEBORATION
void SwapEven(int** arr, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - 1; j++)
		{
			if ((*arr)[j] != 0 && (*arr)[j] % 2 != 0)
				Swap(&(*arr)[j], &(*arr)[j + 1]);
		}
}

int* OrdCreParOrdDecreDisp(int n)
{
	int* arr = (int*)calloc(n, sizeof(int));
	int* arr2 = arr;

	SwapEven(&arr, n);


	int pari = ContaPari(arr, n);
	qsort(arr, pari, sizeof(int*), OrdineCrescenteX);

	arr2 = &arr[pari];
	qsort(arr2, n - pari, sizeof(int*), OrdineDecrescenteY);

	PrintArrayline(arr, n);
	
	return arr;
}


int* MergeArrayOrd(int* arr1, int* arr2, int a, int b)
{
	int* res = (int*)calloc(a + b, sizeof(int));
	for (int i = 0, ai = 0, bi = 0; i < a + b; i++)
	{
		if (ai == a)
		{
			res[i] = arr2[bi];
			bi++;
			continue;
		}
		if (bi == b)
		{
			res[i] = arr1[ai];
			ai++;
			continue;
		}


		if (arr1[ai] < arr2[bi])
		{
			res[i] = arr1[ai];
			ai++;
		}
		else
		{
			res[i] = arr2[bi];
			bi++;
		}

	}
	return res;
}


