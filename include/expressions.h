#ifndef _EXPRESSIONS_H_
#define _EXPRESSIONS_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MAX_EXPRESSIONS 20
#define MAX_ARGUMENT_COUNT 10

#include "lib/vector.h"

#define BIT8_INT_DATATYPE 0
#define BIT16_INT_DATATYPE 1
#define BIT32_INT_DATATYPE 2
#define BIT64_INT_DATATYPE 3
#define STRING_DATATYPE 4
#define FLOAT32_DATATYPE 5
#define FLOAT64_DATATYPE 6
#define INVALID_DATATYPE 7

typedef struct {
    char* name;
    void* value;
    char datatype;
} variable_expr_t;

typedef struct {
    char* name;
    char** arguments;
    char return_type;
    vector_t* tokens;
    int ret_value;
} function_expr_t;

typedef struct {
    int rax;
    void* rdi;
    void* rsi;
    int rdx;
} syscall_expr_t;

typedef enum {
    VARIABLE_EXPR,
    FUNCTION_EXPR,
    SYSCALL_EXPR,
    MACRO_EXPR
} expr_type_t;

typedef struct {
    expr_type_t type;
    void* expr;
} expression_t;


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _EXPRESSIONS_H_ */
