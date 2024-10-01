#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

char* utils_ascii_to_hex(const char* ascii);
bool utils_is_number(char* str);
int utils_cstr_as_number(char* str);
bool utils_is_operator(char* str);
void utils_execute_command(char* command);
bool is_datatype(char* str);
char* utils_replace_filetype(char* cstr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _UTILS_H_ */
