#ifndef _EXPRESSIONS_H_
#define _EXPRESSIONS_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MAX_EXPRESSIONS 20

typedef struct {
    char* name;
    int value;
} variable_expr_t;

typedef struct {
    char* name;
    char** arguments;
    variable_expr_t intern_variables[];
} function_expr_t;

typedef struct {
    char* content;
    char byte_amount;
} write_expr_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _EXPRESSIONS_H_ */
