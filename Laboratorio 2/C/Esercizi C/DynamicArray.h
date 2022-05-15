#pragma once

int* ReadArray(int n);

void PrintArrayline(int* arr, int n);

void PrintArray(int* arr, int n);

int CheckIfOrdered(int* arr, int n, int(*f)(const void*, const void*));

int OrdineCrescenteX(const void* n1, const void* n2);

int OrdineDecrescenteY(const void* n1, const void* n2);

void Swap(int* a, int* b);

int ContaPari(int* arr, int n);

int* OrdCreParOrdDecreDisp(int n);

int* MergeArrayOrd(int* arr1, int* arr2, int a, int b);

void SwapEven(int** arr, int n);
