// parrot.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "parrot.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "post_handler.h"


typedef struct parrot_handler {
    int times;
} parrot_handler;




BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


// This is an example of an exported variable
//PARROT_API int nParrot=0;

// This is an example of an exported function.
//PARROT_API int fnParrot(void)
//{
//	return 42;
//}


extern "C" PARROT_API post_handler_worker_t parrot = {
    "parrot",
    parrot_init,
    parrot_process,
    parrot_free_output,
    NULL
};

PARROT_API void * parrot_init(const char* conf_file) {
    void *h = malloc(sizeof(parrot_handler));
    memset(h, 0, sizeof(parrot_handler));
	fprintf(stderr, "parrot init: %s\n", conf_file);

    ((parrot_handler*)h)->times = strlen(conf_file);
	fprintf(stderr, "parrot init: %d\n", ((parrot_handler*)h)->times);

    return h;
}

PARROT_API char * parrot_process(void *handler, const char* input) {
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

PARROT_API int parrot_free_output(char *output) {
    free(output);
    return 0;
}


// This is the constructor of a class that has been exported.
// see parrot.h for the class definition
/*
CParrot::CParrot()
{ 
	return; 
}*/

