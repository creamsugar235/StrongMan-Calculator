#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Header "\033[95m"
#define EndC "\033[0m"
#define Bold "\033[1m"
#define Underline "\033[4m"
#define Red "\033[31m"
#define Green "\033[92m"
#define Blue "\033[94m"
#define Cyan "\033[96m"
#define White "\033[97m"
#define Yellow "\033[93m"
#define Grey "\033[90m"
#define Black "\033[90m"
#define Default "\033[39m"
#define VARLEN 26
#define PRECLEN 6
#define VALIDLEN 63
#define NUMLEN 11
#define OPLEN 9
#define ORDERLEN 12
#define FUNCLEN 10


typedef struct
{
	size_t size;
	const char* values[];
} stringList;

extern const char* variables[];
extern const char* precedence[];
extern const char* valid[];
extern const char* numbers[];
extern const char* operators[];
extern const char* functions[];

bool CheckSyntax(const char* text);
bool CharInList(char c, const char* str[], size_t size);
unsigned int Count(char c, const char* str);
stringList Evaluate(stringList text);
bool IsIn(char c, const char* str, size_t size);
bool IsInList(const char* s, const char* str[], size_t size);
void Parse(const char* text);
double RunFunction(double x, const char* str);
double SimpleCalc(double a, double b, const char* op);
int Sum(int arr[], unsigned int len);
bool StrEquals(const char* a, const char* b);