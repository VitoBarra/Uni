#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int** ReadMatrix(int n, int m)
{
	int** mat = (int**)calloc(n, sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		mat[i] = (int*)calloc(m, sizeof(int));
		for (int j = 0; j < m; j++)
			scanf("%d", &mat[i][j]);
	}

	return mat;
}

void PrintMatrix(int** mat, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}

void NullDiagonal(int** mat, int n)
{
	for (int i = 0; i < n; i++)
	{
		mat[i][i] = 0;
		mat[i][n - i - 1] = 0;
	}

}



//TODO
void OrdinaPerRiga(int*** mat, int n, int m)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if ((*mat)[j][i] > (*mat)[j][i + 1])
			{
				int* row;
				row = (*mat)[j];
				(*mat)[j] = (*mat)[j + 1];
				(*mat)[j + 1] = row;
			}
			else if ((*mat)[j][i] == (*mat)[j][i + 1])
			{

				if ((*mat)[j + 1][i] > (*mat)[j + 1][i + 1])
				{
					int* row;
					row = (*mat)[j];
					(*mat)[j] = (*mat)[j + 1];
					(*mat)[j + 1] = row;
				}
			}
		}


	}
}