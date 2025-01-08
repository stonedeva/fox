#ifndef TYPE_H
#define TYPE_H

#include "lexer.h"

#define MAX_TYPES 200

typedef enum {
    INTEGER = 1,
    BYTE = 2,
    POINTER = 3,
    BOOLEAN = 4,
    TYPE_INVALID = 5
} VarType;

typedef struct {
    VarType types[MAX_TYPES];
    size_t type_count;
    size_t tok_sz;
    Token* tokens;
    char* filename;
} TypeStack;

TypeStack* typestack_init(Lexer* lexer);
void typestack_evaluate(TypeStack* stack);
void typestack_free(TypeStack* stack);

void typestack_push(TypeStack* stack, VarType type);
VarType typestack_pop(TypeStack* stack);
VarType typestack_type_from_cstr(const char* cstr);
char* typestack_cstr_from_type(VarType type);

#endif // TYPE_H
