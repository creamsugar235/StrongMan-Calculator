#include "main.h"

int main(void)
{
	char text[10000];
	if (!fgets(text, sizeof(text), stdin))
	{
		printf("Error, type something in maybe -_-\n");
	}

	printf("%d %d %d", CharInList('`', operators, OPLEN), CharInList('`', numbers, NUMLEN), CharInList('`', precedence, PRECLEN));
	//Parse(text);
}

const char* leftBrackets[] = {"(", "{", "["};
const char* rightBrackets[] = {")", "}", "]"};

bool CheckSyntax(const char* text)
{
	char lastSignificant;
	const char * c;
	int lastSignificantIndex = 0;
	bool closed = true;
	bool reachedNumber = false;
	int brackets[3] = {0, 0, 0};
	int i;
	for (i = 0; i < strlen(text)-1; i++)
	{
		c = &text[i];
		if (CharInList(*c, valid, VALIDLEN))
		{
			if (CharInList(*c, numbers, NUMLEN) && !reachedNumber)
			{
				reachedNumber = true;
			}
			char line[i + 1];
			line[i] = '\0';
			for (int j = 0; j < i;j++) {line[j] = '~';}
			if (CharInList(*c, operators, OPLEN) && !reachedNumber)
			{
				printf("Error: \n");
				printf("\t%s%s%s\n", Bold, Red, text);
				printf("\t%s%s%c\n", Red, line, '^');
				printf("%sCharacter %d, expected number before operator: \'%s%s%s\'\n", Default, i + 1, Red, c, Default);
				return false;
			}
			if (CharInList(*c, precedence, PRECLEN))
			{
				closed = Sum(brackets, 3) == 0;
				if (CharInList(*c, rightBrackets, 3) && closed)
				{
					printf("Error: \n");
					printf("\t%s%s%s\n", Bold, Red, text);
					printf("\t%s%s%c\n", Red, line, '^');
					printf("%sCharacter %d, mis-matched brackets \'%s%s%s\'\n", Default, i + 1, Red, c, Default);
					return false;
				}
				if (CharInList(*c, leftBrackets, 3))
				{
					switch(*c)
					{
						case '(':
							brackets[0]++;
						case '{':
							brackets[1]++;
						case '[':
							brackets[2]++;
						case ')':
							brackets[0]--;
						case '}':
							brackets[1]--;
						case ']':
							brackets[2]--;
					}
				}
				char line2[lastSignificantIndex + (i - lastSignificantIndex) + 1];
				line2[lastSignificantIndex + (i - lastSignificantIndex)] = '\0';
				for (int j = 0; j < lastSignificantIndex + (i - lastSignificantIndex); j++) {line2[j] = '~';}
				if (CharInList(lastSignificant, operators, OPLEN))
				{
					if (CharInList(*c, operators, OPLEN))
					{
						printf("Error: \n");
						printf("\t%s%s%s\n", Bold, Red, text);
						printf("\t%s%s%c\n", Red, line2, '^');
						printf("%sCharacter %d, unexpected operator: \'%s%s%s\'\n", Default, i + 1, Red, c, Default);
						return false;
					}
				}
				if (*c != ' ')
				{
					lastSignificant = *c;
					lastSignificantIndex = i;
				}
			}
		}
		else
		{
			char line[i + 1];
			line[i] = '\0';
			for (int j = 0; j < i;j++) {line[j] = '~';}
			printf("Error: \n");
			printf("\t%s%s%s\n", Bold, Red, text);
			printf("\t%s%s%c\n", Red, line, '^');
			printf("%sCharacter %d, invalid character \'%s%s%s\'\n", Default, i + 1, Red, c, Default);
			return false;
		}
	}
	char line2[lastSignificantIndex + (i - lastSignificantIndex) + 1];
	line2[lastSignificantIndex + (i - lastSignificantIndex)] = '\0';
	for (int j = 0; j < lastSignificantIndex + (i - lastSignificantIndex); j++) {line2[j] = '~';}
	if (IsInList(&lastSignificant, operators, OPLEN))
	{
		printf("Error: \n");
		printf("\t%s%s%s\n", Bold, Red, text);
		printf("\t%s%s%c\n", Red, line2, '^');
		printf("%sCharacter %ld, unexpected operator: \'%s%s%s\n\'", Default, strlen(text), Red, c, Default);
		return false;
	}
	closed = Sum(brackets, 3) == 0;
	if (!closed)
	{
		printf("Error: ");
		printf("Incomplete bracket formatting");
		return false;
	}
	return true;
}

void Clear(char* c)
{
	for (size_t i = 0; i < sizeof(c); i++)
	{
		c[i] = '\0';
	}
}

void Parse(const char* text)
{
	if (!CheckSyntax(text))
		return;
	int ind = 0;
	char newText[strlen(text) - Count(' ', text)];
	printf("%ld\n", strlen(text));
	for (size_t n = 0; n < strlen(text); n++)
	{
		if (text[n] != ' ')
		{
			newText[ind] = text[n];
			ind++;
		}
	}
	newText[ind] = '\0';
	printf("%s", newText);
	const unsigned int len = sizeof(newText) - 1; //since sizeof char is 1 you don't have to divide by the sizeof char
	char* symbols[len];
	unsigned int symbolLen = 0;
	char current[10000];
	unsigned int currLen = 0;
	for (int i = 0; i < len; i++)
	{
		printf("%c %d, %d\n", newText[i], CharInList(newText[i], operators, OPLEN), CharInList(newText[i], precedence, PRECLEN));
		if (CharInList(newText[i], operators, OPLEN) || CharInList(newText[i], precedence, PRECLEN))
		{
			printf("C: %s", current);
			if (currLen)
			{
				symbols[symbolLen] = (char*)malloc(currLen + 1);
				strcpy(symbols[symbolLen], current);
				symbolLen++;
			}
			symbols[symbolLen] = (char*)calloc(newText[i], 2);
			symbols[symbolLen][1] = '\0';
			symbolLen++;
			Clear(current);
			currLen = 0;
		}
		if (!CharInList(newText[i], operators, OPLEN) && !CharInList(newText[i], precedence, PRECLEN))
		{
			current[currLen++] = newText[i];
			current[currLen+1] = '\0';
		}
		printf("bruh: %s\n", symbols[symbolLen]);
	}
	if (currLen)
	{
		symbols[symbolLen] = (char*)malloc(currLen + 1);
		strcpy(symbols[symbolLen], current);
		symbolLen++;
	}
	stringList s;
	s.size = symbolLen;
	for (size_t i = 0; i < symbolLen; i++)
	{
		printf("%s\n", symbols[i]);
		s.values[i] = symbols[i];
	}
}