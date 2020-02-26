#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parrot.h"
#include "post_handler.h"

//struct post_handler_worker_t;

typedef struct parrot_handler {
    int times;
} parrot_handler;

EXPORT void * parrot_init(const char* conf_file) {
    void *h = malloc(sizeof(parrot_handler));
    memset(h, 0, sizeof(parrot_handler));
    ((parrot_handler*)h)->times = strlen(conf_file);
    return h;
}


EXPORT char * parrot_process(void *handler, const char* input) {
    int size = 0;
    char *output;

    parrot_handler* h = (parrot_handler*)handler;

    if (input == NULL)
        return NULL;

    size = strlen(input);

    fprintf(stderr, "parrot process: %s\n", input);
    output = (char *)malloc(size * h->times + 1);
    for (int i = 0; i < h->times; i++) {
        strcpy(output + i * size, input);
    }

    output[size * h->times] = 0;

    return output;
}

EXPORT int parrot_free_output(char *output) {
    free(output);
    return 0;
}

