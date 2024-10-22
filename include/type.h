#ifndef TYPE_H
#define TYPE_H

#include "lexer.h"

#define MAX_TYPES 200

typedef enum {
    INTEGER,
    BYTE,
    POINTER,
    BOOLEAN
} VarType;

typedef struct {
    VarType types[MAX_TYPES];
    size_t type_count;
    size_t tok_sz;
    Token* tokens;
    char* filename;
} TypeStack;

TypeStack* typestack_init(Lexer* lexer);
void typestack_free(TypeStack* stack);

void typestack_push(TypeStack* stack, VarType type);
VarType typestack_pop(TypeStack* stack);

#endif // TYPE_H
