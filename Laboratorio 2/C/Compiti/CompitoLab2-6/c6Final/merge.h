#include <stdlib.h>
#include <stdio.h>
/***Funzione che prende due array long ordinati e le loro dimensioni, e restituisce
*** un altro array long ordinato, contenente tutti gli elementi degli array originali (merge)
*** Gli array originali vengono deallocati. */

long *mergeAndFree(long *a, int na, long *b, int nb)
{
	long *res = malloc((na + nb) * sizeof(long));
	int i = 0, j = 0;
	while (i < na && j < nb)
	{
		if (a[i] < b[j])
		{
			res[i + j] = a[i];
			i++;
		}
		else
		{
			res[i + j] = b[j];
			j++;
		}
	}

	while (i < na)
	{
		res[i + j] = a[i];
		i++;
	}

	while (j < nb)
	{
		res[i + j] = b[j];
		j++;
	}

	free(a);
	free(b);
	return res;
}