#include "lib/utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* utils_ascii_to_hex(const char* ascii) {
    size_t len = strlen(ascii);
    char* hex_str = (char*)malloc((len * 3 + 1) * sizeof(char));
    if (hex_str == NULL)
	return NULL;

    char* pointer = hex_str;
    for (size_t i = 0; i < len; i++)
	pointer += sprintf(pointer, "%02x", (unsigned char)ascii[i]);

    if (pointer > hex_str)
	*(pointer - 1) = '\0';

    return hex_str;
}

bool utils_is_number(char* str) {
    while (*str != '\0') {
	if (!isdigit(*str)) 
	    return false;
	str++;
    }
    return true;
}

int utils_cstr_as_number(char* str) {
    int result = 0;
    while (*str != '\0') {	
	if (isdigit((unsigned char)*str))
	    result = result * 10 + (*str - '0');
	str++;
    }
    return result;
}

void utils_execute_command(char* command) {
    printf("[CMD] %s\n", command);
    system(command);
}

