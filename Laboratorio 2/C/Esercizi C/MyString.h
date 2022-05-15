struct StrLen
{
	int len;
	char* s;
};
typedef struct StrLen StrLen;

StrLen* ReadStrLen(int n);
void PrintArrStrLen(StrLen* arr, int n);
char* en2piglatin(char* s);
char* AllToUpper(char* s);
char* AllToLower(char* s);
int isVowel(char c);
int IsWhiteSpace(char c);
int IsPalindrome(char* s, int ls, int i);
int OrdLexicographical(const void* n1, const void* n2);
int OrdStringLength(const void* n1, const void* n2);
void encode(char* str);
