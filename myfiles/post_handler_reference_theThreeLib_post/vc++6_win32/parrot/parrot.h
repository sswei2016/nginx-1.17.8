

#include "post_handler.h"
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PARROT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PARROT_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef PARROT_EXPORTS
#define PARROT_API __declspec(dllexport)
#else
#define PARROT_API __declspec(dllimport)
#endif

// This class is exported from the parrot.dll
/*
class PARROT_API CParrot {
public:
	CParrot(void);
	// TODO: add your methods here.
};
*/

//extern "C"  PARROT_API int nParrot;
//extern "C" PARROT_API int fnParrot(void);

extern "C" PARROT_API post_handler_worker_t parrot;

extern "C" PARROT_API void * parrot_init(const char* conf_file);
extern "C" PARROT_API char * parrot_process(void *handler, const char* input);
extern "C" PARROT_API void * parrot_init(const char* conf_file);
extern "C" PARROT_API int parrot_free_output(char *output);
