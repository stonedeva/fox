#include "lib/utils.h"
#include <string.h>
#include <stdio.h>

bool utils_is_number(char* str) 
{
    while (*str != '\0') {
	if (!isdigit(*str)) 
	    return false;
	str++;
    }
    return true;
}

int utils_cstr_as_number(char* str) 
{
    int result = 0;
    while (*str != '\0') {	
	if (isdigit((unsigned char)*str))
	    result = result * 10 + (*str - '0');
	str++;
    }
    return result;
}

bool utils_is_operator(char* str) 
{
    if (strcmp(str, "==") == 0 ||
	strcmp(str, "!=") == 0 ||
	strcmp(str, "&&") == 0 ||
	strcmp(str, "||") == 0) {
	return true;
    }

    switch (str[0]) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '=':
    case '<':
    case '>':
    case '%':
	return true;
    }

    return false;
}

char* utils_replace_filetype(char* cstr)
{
    size_t len = strlen(cstr);
    cstr[len - 1] = 'm';
    cstr[len - 2] = 's';
    cstr[len - 3] = 'a';
    
    printf("STRING: %s\n", cstr);

    return cstr;
}
