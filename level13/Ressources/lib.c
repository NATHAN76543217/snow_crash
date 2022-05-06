/*
**	The _GNU_SOURCE feature test macro must be defined in order to
**	obtain the definitions of RTLD_DEFAULT and RTLD_NEXT from
**	<dlfcn.h>.
*/

# define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>

/*
// #define DECLARE_GETUID(getuid)								    		\
// static uid_t	(*original_##getuid)() = NULL;							\
//                                                                         \
// uid_t   getuid( void )	            							    	\
// {    																	\
// 	dprintf(STDOUT_FILENO, "My function\n");							\
//     uid_t uid = 0;                                                      \
//     if (original_##getuid == NULL)										\
// 	{																	\
// 		original_##getuid = dlsym(RTLD_NEXT, #getuid);			    	\
// 		if (original_##getuid == NULL)									\
// 		{																\
// 			dprintf(STDERR_FILENO, "Error in dlsym: %s\n", dlerror());	\
// 			return 0;													\
// 		}																\
// 	}		                                                            \
//                                                                         \
// 	uid = original_##getuid();											\
//     if (uid == 2013 || uid == 501)										\
// 		return 4242;                                                    \
// 	return uid;															\
// }
*/

// DECLARE_GETUID(getuid);
// DECLARE_GETUID(getuid32);

#define DECLARE_STRDUP(strdup)								    		\
static  char*	(*original_##strdup)(const char *) = NULL;				\
                                                                        \
char*   strdup( const char* s )	            							\
{    																	\
	dprintf(STDOUT_FILENO, "My function\n");							\
    if (original_##strdup == NULL)										\
	{																	\
		original_##strdup = dlsym(RTLD_NEXT, #strdup);			    	\
		if (original_##strdup == NULL)									\
		{																\
			dprintf(STDERR_FILENO, "Error in dlsym: %s\n", dlerror());	\
			return 0;													\
		}																\
	}		                                                            \
                                                                        \
	return original_##strdup(s);											\
}

DECLARE_STRDUP(strdup);