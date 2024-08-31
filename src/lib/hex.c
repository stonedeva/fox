#include "lib/hex.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* ascii_to_hex(const char* ascii) {
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
