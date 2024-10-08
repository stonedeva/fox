#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUILD_TARGETS 30

typedef struct {
    char* cflags;
    char* paths[MAX_BUILD_TARGETS];
    size_t path_count;
    char* output;
} Builder;

/*
 * Public
*/
Builder* cb_init(char* output);
void cb_free(Builder* builder);
void cb_build(Builder* builder);
void cb_set_cflags(Builder* builder, char* cflags);
void cb_add_target(Builder* builder, char* target);

/*
 * Private
*/
static char* _cb_construct(Builder* builder);

#ifdef CB_IMPLEMENTATION

Builder* cb_init(char* output)
{
    Builder* builder = (Builder*)malloc(sizeof(Builder));
    if (!builder) {
	perror("Memory allocation failed for Builder!");
	exit(1);
    }

    builder->output = output;

    return builder;
}

void cb_free(Builder* builder)
{
    free(builder);
}

void cb_add_target(Builder* builder, char* path)
{
    size_t path_count = builder->path_count;
    if (path_count >= MAX_BUILD_TARGETS) {
	fprintf(stderr, "CrossBuild: Too many build targets provided!\n");
	return;
    }
    builder->paths[path_count] = path;
    builder->path_count++;
}

void cb_build(Builder* builder)
{
    printf("[BUILD] Targets:\n");
    for (size_t i = 0; i < builder->path_count; i++) {
	printf(" - %s\n", builder->paths[i]);
    }

    if (builder->cflags != NULL) {
	printf("[BUILD] CFlags: %s\n", builder->cflags);
    }

    printf("\n[BUILD] Start compilation...\n");

    char* command = _cb_construct(builder);
    system(command);

    printf("[BUILD] %s\n", command);
}

void cb_set_cflags(Builder* builder, char* cflags)
{
    builder->cflags = cflags;
}

/*
 * Private
*/
static char* _cb_construct(Builder* builder)
{
    char* cflags = builder->cflags;
    char** paths = builder->paths;
    size_t path_count = builder->path_count;
    
    char* command = (char*)malloc(sizeof(char) * 200);

#if defined(__unix__) || defined(__APPLE__)
    strcpy(command, "cc");
#elif __WIN32
    strcpy(command, "mingw.exe");
#else
    fprintf(stderr, "[BUILD] Error: Unknown operating system!\n");
    exit(1);
#endif

    if (cflags != NULL && strlen(cflags) > 0) {
	strcat(command, " ");
	strcat(command, cflags);
    }

    strcat(command, " ");
    
    for (size_t i = 0; i < path_count; i++) {
	strcat(command, paths[i]);
	if (i < path_count - 1) {
	    strcat(command, " ");
	}
    }

    strcat(command, " -o ");
    strcat(command, builder->output);

    return command;
}

#endif // CROSSBUILD_IMPLEMENTATION
