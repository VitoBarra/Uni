#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h> 
#include "MyString.h"


//I/O

StrLen* ReadStrLen(int n)
{
	StrLen* arr = (StrLen*)calloc(n, sizeof(StrLen));
	for (int i = 0; i < n; i++)
	{
		arr[i] = *((StrLen*)malloc(sizeof(StrLen)));
		arr[i].s = (char*)calloc(100, sizeof(char));
		scanf("%s", arr[i].s);
		arr[i].len = strlen(arr[i].s);
	}
	return arr;
}


void PrintArrStrLen(StrLen* arr, int n)
{
	for (int i = 0; i < n; i++)
		printf("%s\n", arr[i].s);
}

//ELABORATION STRING

char* en2piglatin(char* s)
{
	if (s == NULL) return NULL;
	char* str = (char*)calloc(100, sizeof(char));
	strcpy(str, s);
	int vow = isVowel(str[0]);
	int upper = str[0] > 64 && str[0] < 91 ? 1 : 0;

	if (vow == 1)
	{
		str[strlen(str)] = 'w';
		str[strlen(str)] = 'a';
		str[strlen(str)] = 'y';
	}

	else
	{
		if (str[0] == 'y' || str[0] == 'Y')
		{
			str[strlen(str)] = tolower(str[0]);
			str = &str[1];
		}
		for (; !isVowel(str[0]) && str[0] != 'y' && str[0] != 'Y'; str[strlen(str)] = tolower(str[0]), str = &str[1])
			;


		if (upper == 1)
			str[0] = toupper(str[0]);


		str[strlen(str)] = 'a';
		str[strlen(str)] = 'y';

	}
	return str;
}


char* AllToUpper(char* s)
{
	char str[100] = "";
	strcpy(str, s);
	for (int i = 0; i < strlen(str); i++)
	{
		if (!IsWhiteSpace(str[i]))
			str[i] = toupper(str[i]);
	}
	return str;
}

char* AllToLower(char* s)
{
	char str[100] = "";
	strcpy(str, s);
	for (int i = 0; i < strlen(str); i++)
	{
		if (!IsWhiteSpace(str[i]))
			str[i] = tolower(str[i]);
	}
	return str;
}


//PROPERTY

int isVowel(char c)
{
	return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') || (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

int IsWhiteSpace(char c)
{
	return(c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int IsPalindrome(char* s, int ls, int i)
{
	if (s[i] == ' * ')return 1;
	if (s[i] != s[ls - 1])return 0;
	return IsPalindrome(s, ls - 1, i + 1);
}


//ORDERS FUCTION

int OrdLexicographical(const void* n1, const void* n2)
{
	StrLen a = *((StrLen*)n1);
	StrLen b = *((StrLen*)n2);

	if (strcmp(a.s, b.s) > 0)
		return 0;
	else if (strcmp(a.s, b.s) == 0)
		return a.len < b.len > 0 ? 0 : 1;
	else
		return 1;
}

int OrdStringLength(const void* n1, const void* n2)
{
	StrLen a = *((StrLen*)n1);
	StrLen b = *((StrLen*)n2);

	if (a.len < b.len> 0)
		return 0;
	else if (a.len == b.len)
		return strcmp(a.s, b.s) > 0 ? 0 : 1;
	else
		return 1;
}

void encode(char* str)
{
	char* a = (char*)calloc(15, sizeof(char));
	strcpy(a, str);

	for (int i = 0; i < strlen(a); i++)
	{
		a[i] = toupper(a[i]);
	}


	for (int i = 0; i < strlen(a); i++)
	{
		if ((int)a[i] > 86)
			a[i] = 64 + (4 - (90 - (int)a));
		else
		{
			a[i] = (int)a[i] + 4;
		}
	}
	return a;
}