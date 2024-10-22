#define CB_IMPLEMENTATION
#include "./cbuild.h"

int main(void)
{
    Builder* builder = cb_init("build/foxc");
    cb_set_cflags(builder, "-I include -g");

    cb_add_target(builder, "src/main.c");
    cb_add_target(builder, "src/lexer.c");
    cb_add_target(builder, "src/error.c");
    cb_add_target(builder, "src/context.c");
    cb_add_target(builder, "src/compiler.c");
    cb_add_target(builder, "src/type.c");
    cb_add_target(builder, "src/lib/utils.c");
    
    cb_build(builder);
}
