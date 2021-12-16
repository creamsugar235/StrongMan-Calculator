#include "main.h"
const char* variables[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l",
"m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

const char* precedence[] = {"(", ")",  "{", "}", "[", "]"};

const char* valid[] = {"=", "+", "-", "(", ")", ".", ",", "/", "*", "&", "^",
"%", "{", "}", "[", "]", "|", "~", "log", "sin", "cos", "tan", "asin",
"acos", "atan", "atan2", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
"k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " "};

const char* numbers[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."};

const char* operators[] = {"+", "-", "*", "/", "%", "^", "&", "|", "~"};

const char* order[] = {"(", "{", "[", "^", "*", "/", "%", "+", "-", "&", "|", "~"};

const char* functions[] = {"log", "sin", "cos", "tan", "asin", "acos", "atan", "fac", "flr", "ceil"};


bool CharInList(char c, const char* str[], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (str[i] == '\0')
			return false;
		if (c == *str[i])
			return true;
	}
	return false;
}

unsigned int Count(char c, const char* str)
{
	unsigned int count = 0;
	for(size_t i = 0; i < strlen(str); i++)
	{
		if (c == str[i])
			count++;
	}
	return count;
}

bool IsIn(char c, const char* str, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (str[i] == '\0')
		{
			return false;
		}
		if (c == str[i])
		{
			return true;
		}
	}
	return false;
}

bool IsInList(const char* s, const char* str[], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (StrEquals(s, str[i]))
		{
			return true;
		}
	}
	return false;
}

int Sum(int arr[], unsigned int len)
{
	int s = 0;
	for (int i = 0; i < len; i++)
	{
		s += arr[i];
	}
	return s;
}

bool StrEquals(const char* a, const char* b)
{
	if (strlen(a) != strlen(b))
	{
		return false;
	}
	for (size_t i = 0; i < strlen(a); i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}