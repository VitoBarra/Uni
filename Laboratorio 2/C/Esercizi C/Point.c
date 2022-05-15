#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
struct Point
{
	float x;
	float y;
};
typedef struct Point Point;

double DistanzaEuclidea(Point p1, Point p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}


int OrdineCrescenteX(const void* n1, const void* n2)
{
	//qsort(arr, n , sizeof(int*), OrdineCrescente);
	Point a = *((Point*)n1);
	Point b = *((Point*)n2);


	if (a.x > b.x)
		return 1;
	else if (a.x == b.x)
		return 0;
	else
		return -1;
}
int OrdineDecrescenteY(const void* n1, const void* n2)
{
	//qsort(arr, n , sizeof(int*), OrdineDecrescente);
	Point a = *((Point*)n1);
	Point b = *((Point*)n2);


	if (a.y < b.y)
		return 1;
	else if (a.y == b.y)
		return 0;
	else
		return -1;
}

void PrinPoint(Point* arr, int n, Point* a)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (DistanzaEuclidea(arr[i], *a) < 5)
			printf("%.2f %.2f\n", arr[i].x, arr[i].y);
	}
}


Point* ReadPoint( int n)
{
	Point* arr = (Point*)calloc(n, sizeof(Point));
	for (int i = 0; i < n; i++)
		scanf("%f %f", &(arr[i].x), &(arr[i].y));
	return arr;
}