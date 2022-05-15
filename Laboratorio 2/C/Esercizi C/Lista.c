#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int v;
	struct Node* next;
};
typedef struct Node Node;
typedef struct Node* List;
typedef enum { false, true } boolean;


//ADD ELEMENT
void AddheadNode(List* ptrlist, Node* node)
{
	if (*ptrlist != NULL)
	{
		node->next = *ptrlist;
		*ptrlist = node;
	}
	else
		*ptrlist = node;
}

void Addhead(List* ptrlist, int n)
{
	Node* newNodePtr = (Node*)malloc(sizeof(Node));
	newNodePtr->v = n;
	newNodePtr->next = NULL;

	AddheadNode(ptrlist, newNodePtr);
}


void AddTailNode(List* ptrlist, Node* node)
{
	if (*ptrlist != NULL)
	{
		Node* i = *ptrlist;
		for (; i->next != NULL; i = i->next);
		i->next = node;
	}
	else
		*ptrlist = node;
}


void AddTail(List* ptrlist, int n)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->v = n;
	NewNode->next = NULL;

	AddTailNode(ptrlist, NewNode);
}

void AddOrederedWithRepCre(List* ptrlist, int n)
{
	Node* newNodePtr = (Node*)malloc(sizeof(Node));
	newNodePtr->v = n;
	newNodePtr->next = NULL;


	if (*ptrlist == NULL)
		*ptrlist = newNodePtr;
	else for (Node* i = *ptrlist; i != NULL; i = i->next)
	{
		if (n <= i->v) // caso primo
		{
			newNodePtr->next = i;
			*ptrlist = newNodePtr;
			break;
		}
		// n>v
		if (i->next == NULL)// caso ultimo
		{
			i->next = newNodePtr;
			break;
		}
		//i->next != NULL
		if (n <= i->next->v) //caso in mezzo
		{
			newNodePtr->next = i->next;
			i->next = newNodePtr;
			break;
		}
	}
}
void AddOrederedWithRepDecre(List* ptrlist, int n)
{
	Node* newNodePtr = (Node*)malloc(sizeof(Node));
	newNodePtr->v = n;
	newNodePtr->next = NULL;


	if (*ptrlist == NULL)
		*ptrlist = newNodePtr;
	else for (Node* i = *ptrlist; i != NULL; i = i->next)
	{
		if (n >= i->v) // caso primo
		{
			newNodePtr->next = i;
			*ptrlist = newNodePtr;
			break;
		}
		// n<v
		if (i->next == NULL)// caso ultimo
		{
			i->next = newNodePtr;
			break;
		}
		//i->next != NULL
		if (n >= i->next->v) //caso in mezzo
		{
			newNodePtr->next = i->next;
			i->next = newNodePtr;
			break;
		}
	}
}

void AddOrederedNoRepCre(List* ptrlist, int n)
{
	Node* newNodePtr = (Node*)malloc(sizeof(Node));
	newNodePtr->v = n;
	newNodePtr->next = NULL;


	if (*ptrlist == NULL)
		*ptrlist = newNodePtr;
	else for (Node* i = *ptrlist; i != NULL; i = i->next)
	{
		if (n < i->v) // caso primo
		{
			newNodePtr->next = i;
			*ptrlist = newNodePtr;
			break;
		}
		else if(n == i->v)
		{
			free(newNodePtr);
			break;
		}
		// n>v
		if (i->next == NULL)// caso ultimo
		{
			i->next = newNodePtr;
			break;
		}
		//i->next != NULL
		if (n < i->next->v) //caso in mezzo
		{
			newNodePtr->next = i->next;
			i->next = newNodePtr;
			break;
		}
		else if(n == i->next->v)
		{
			free(newNodePtr);
			break;
		}

	}
}
void AddOrederedNoRepDecre(List* ptrlist, int n)
{
	Node* newNodePtr = (Node*)malloc(sizeof(Node));
	newNodePtr->v = n;
	newNodePtr->next = NULL;


	if (*ptrlist == NULL)
		*ptrlist = newNodePtr;
	else for (Node* i = *ptrlist; i != NULL; i = i->next)
	{
		if (n > i->v) // caso primo
		{
			newNodePtr->next = i;
			*ptrlist = newNodePtr;
			break;
		}
		else if (n == i->v)
		{
			free(newNodePtr);
			break;
		}
		// n>v
		if (i->next == NULL)// caso ultimo
		{
			i->next = newNodePtr;
			break;
		}
		//i->next != NULL
		if (n > i->next->v) //caso in mezzo
		{
			newNodePtr->next = i->next;
			i->next = newNodePtr;
			break;
		}
		else if (n == i->next->v)
		{
			free(newNodePtr);
			break;
		}

	}
}

void AddInPosition(List* ptrlist, int pos, int n)
{
	Node* newNodePtr = (Node*)malloc(sizeof(Node));
	newNodePtr->v = n;
	newNodePtr->next = NULL;

	if (*ptrlist == NULL)
	{
		Node* j = *ptrlist;
		for (int i = 0; j->next != NULL && i < pos - 2; i++, j = j->next);
		if (j->next != NULL)
			newNodePtr->next = j->next;

		j->next = newNodePtr;
	}
	else
		*ptrlist = newNodePtr;


}

//REMOVE


void Remove(List* ptrlist, int n)
{
	if (*ptrlist != NULL)
	{
		if ((*ptrlist)->v == n)
		{
			Node* temp = *ptrlist;
			*ptrlist = temp->next;
			free(temp);
		}
		else
			for (Node* i = *ptrlist; i->next != NULL; i = i->next)
			{

				if (i->next->v == n)
				{
					Node* temp = i->next;
					if (temp != NULL)
						i->next = temp->next;
					else
						i->next = NULL;
					free(temp);
					break;
				}
			}
	}
}

void RemoveFristNelement(List* ptrlist, int n)
{
	if (*ptrlist != NULL)
		for (int i = 0; *ptrlist != NULL && i < n; i++, *ptrlist = (*ptrlist)->next);
}

void RemoveMultipleOf(List* ptrlist, int n)
{
	while ((*ptrlist) != NULL && (*ptrlist)->v % n == 0)
		*ptrlist = (*ptrlist)->next;
	for (List i = *ptrlist; i != NULL && i->next != NULL; i = i->next)
	{
		if (i->next->v % n == 0)
			i->next = i->next->next;
	}
}

//LIST ELABORATION

List InterSec(List ptrlist1, List ptrlist2)
{
	List result = NULL;
	for (List i = ptrlist1; i != NULL; i = i->next)
		for (List j = ptrlist2; j != NULL; j = j->next)
			if (i->v == j->v)
			{
				AddOrederedNoRepCre(&result, i->v);
				break;
			}

	return result;
}

List MergeListWithRep(List ptrlist1, List ptrlist2)
{
	List result = NULL;
	for (List i = ptrlist1; i != NULL; i = i->next)
		AddOrederedWithRepCre(&result, i->v);
	for (List i = ptrlist2; i != NULL; i = i->next)
		AddOrederedWithRepCre(&result, i->v);

	return result;
}

int SummaElementi(List ptrlist)
{
	int sum = 0;
	for (List i = ptrlist; i != NULL; i = i->next)
		sum += i->v;

	return sum;
}

int ContaFilter(List ptrlist, int n, int (*f)(int, int))
{
	int num = 0;
	for (List i = ptrlist; i != NULL; i = i->next)
		if (f(n, i->v) == 1)num++;
	return num;
}

int MultiplyListBtwRange(List ptrlist, int n, int m)
{
	int mul = 1;
	for (List i = ptrlist; i != NULL; i = i->next)
	{
		if (i->v > n)
		{
			if (i->v >= m)
				break;
			mul *= i->v;
		}
	}
	if (mul == 1)
		return -1;
	return mul;
}

void FillList(List ptrlist)
{
	if (ptrlist == NULL) return;

	for (List i = ptrlist; i->next != NULL; i = i->next)
	{
		if (i->v - i->next->v > 1)
		{
			Node* NewNodeptr = (Node*)malloc(sizeof(Node));
			NewNodeptr->v = i->v - 1;
			NewNodeptr->next = i->next;
			i->next = NewNodeptr;
		}
	}
}



void AddMarkerToEvenRec(List ptrlist)
{
	if (ptrlist == NULL || ptrlist->next == NULL) return;
	if (ptrlist->next->v % 2 == 0)
	{
		Node* t = (Node*)malloc(sizeof(Node));
		t->v = -1;
		t->next = ptrlist->next;
		ptrlist->next = t;
		AddMarkerToEvenRec(t->next);
	}
	else
		AddMarkerToEvenRec((ptrlist->next));

}

void AddMarkerToEven(List* ptrlist)
{
	if ((*ptrlist)->v % 2 == 0)
	{
		Node* t = (Node*)malloc(sizeof(Node));
		t->v = -1;
		t->next = (*ptrlist);
		(*ptrlist) = t;

	}
	AddMarkerToEvenRec((*ptrlist)->next);
}



//PROPERTY CHECK
void CheckOrder(List ptrlist, int n, boolean b)
{
	if (!b) { printf("False\n"); return; }
	else if (ptrlist == NULL || ptrlist->next == NULL)
		printf("True \n");
	else
		CheckOrder(ptrlist->next, ptrlist->v, ptrlist->v > n ? true : false);

}


//I/O

void ReadListPosiv(List* ptrlist, void (*AddingMode)(List*,int))
{
	int elem;

	do
	{
		if (scanf("%d", &elem) && elem >= 0)
			AddingMode(ptrlist, elem);
	} while (elem >= 0);

}
void ReadListPosivErM(List* ptrlist, void (*AddingMode)(List*, int))
{
	int elem;

	do
	{
		if (scanf("%d", &elem) && elem >= 0)
			AddingMode(ptrlist, elem);
		else
		{
			printf("Inserisci intero positivo o -n per uscire\n");
			getchar();
		}
	} while (elem >= 0);

}

void ReadListUnitil0(List* ptrlist, void (*AddingMode)(List*, int))
{
	int elem;

	do
	{
		if (scanf("%d", &elem) && elem > 0)
			AddingMode(ptrlist, elem);
	} while (elem != 0);

}

void ReadListUnitil0ErM(List* ptrlist, void (*AddingMode)(List*, int))
{
	int elem;

	do
	{
		if (scanf("%d", &elem) && elem > 0)
			AddingMode(ptrlist, elem);
		else if (elem != 0)
		{
			printf("Inserisci intero positivo o 0 per uscire\n");
			getchar();
		}
	} while (elem != 0);

}




void Stampa(List ptrlist)
{
	if (ptrlist != NULL)
		for (List i = ptrlist; i != NULL; i = i->next)
			printf("%d\n", i->v);
}

void StampaLinea(List ptrlist)
{
	if (ptrlist == NULL)printf("NULL \n");
	for (List i = ptrlist; i != NULL; i = i->next)
	{
		printf("%d -> ", i->v);
		if (i->next == NULL)
			printf("NULL \n");
	}
}

void StampaLinea2(List ptrlist)
{
	if (ptrlist == NULL)printf("NULL \n");
	for (List i = ptrlist; i != NULL; i = i->next)
	{
		printf("%d --> ", i->v);
		if (i->next == NULL)
			printf("NULL \n");
	}
}

void RecStampaInversa(List ptrlist)
{
	if (ptrlist == NULL) return;
	RecStampaInversa(ptrlist->next);
	printf("%d->", ptrlist->v);
}
void RecStampa(List listptr)
{
	if (listptr == NULL) { return; }
	printf("%d->", listptr->v);
	RecStampa(listptr->next);
}
