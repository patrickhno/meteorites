
// Copyright (C) 1997-1998 Reality Systems as
// All rights reserved.

#define POSIX_INTERNAL
#include <posix/stdlib.h>
#include "Process_startup.h"
#include <Interface/Garbage.h>

struct ThreadArgs{
	int		argc;
	char	**argv;
};

void ProcessThread(ThreadArgs *a){
	#ifdef _DEBUG
	extern void Initialize_Debug(void);
	Initialize_Debug();
	#endif
	delete new Startup(a->argc,a->argv);
	#ifdef _DEBUG
	extern void Deinitialize_Debug(void);
	Deinitialize_Debug();
	#endif
	system_CollectAllGarbage();
	#ifdef _DEBUG
	memory_shutdown();
	#endif
}
