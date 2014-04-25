
// Copyright (C) 1997-1998 Reality Systems as
// All rights reserved.

// Windows specific stuff

#include <windows.h>
#include <posix/stdlib.h>
#include <time.h>
#include "Process_startup.h"
#include <Interface/Debug.h>
#include <Interface/rme_Memory.h>
#include <Interface/Kernel.h>

struct ThreadArgs{
	int		argc;
	char	**argv;
};

/*
DWORD QueueUserAPC( PAPCFUNC pfnAPC, 
 // pointer to APC function 
 
HANDLE hThread, 
 // handle to the thread 
 
DWORD dwData 
 // argument for the APC function 
 
); 
*/

//static void APCThread(void){
//	printf("APCThread: Sleeping...\n");
//	SleepEx(INFINITE,true);
//	printf("APCThread: Interrupted\n");
//	//while(true);
//}

#include <Interface/Process.h>

/*
static void MessageThread(Process *proc){
	Semaphore *sem = proc->sem;
	while(true){
		sem->Acquire();
		// Wee have messages
		printf("Process: Received message\n");
		sem->Release();
	}
}
*/

//#include "GameDLL.h"

typedef void (*print_func)(char *);

#include <Interface/globals.h>

#ifdef _DEBUG
__declspec(dllexport) void *Constructor(Process *proc, Host *hst, Driver *drv, print_func pf, int adrv, HANDLE con, DynamicArray *Input, DynamicArray *Stats, struct MemEnt *_last, void *(*al)(int,int,char*,int), void (*fre)(void*,char*,int), void *(*real)(void*,int,char*,int), double speed){
#else
__declspec(dllexport) void *Constructor(Process *proc, Host *hst, Driver *drv, print_func pf, int adrv, HANDLE con, DynamicArray *Input, DynamicArray *Stats, struct MemEnt *_last, void *(*al)(int,int), void (*fre)(void*), void *(*real)(void*,int), double speed){
#endif

	__globals::SetSpeed(speed);

//	extern Driver *Drivers;
//	extern Host *host;
//	host = proc->KernelHost;
//	Drivers = proc->KernelDrivers;

	#ifdef _DEBUG
	//extern DynamicArray *DebugStats;
	//DebugStats = Stats;
	//extern struct MemEnt *last;
	//last = _last;
	#endif

//	extern struct MemoryHeap *first;
//	first = heap;
//extern class Heap *first_heap;
//extern class Semaphore *heap_sem;
//extern struct Fragment **Fragments;
//	first_heap = heap;
//	heap_sem = sem;
//	Fragments = frags;

	#ifdef _DEBUG
	init_Memory(al,fre,real,0);
	#else
	init_Memory(al,fre,real);
	#endif
/*
	Allocate	= al;
	Free		= fre;
	ReAllocate	= real;
*/
	extern Driver *Drivers;
	extern Host *host;
	host = hst;
	Drivers = drv;

	extern print_func stdio_print;
	stdio_print = pf;
//	extern double StartTime;
//	StartTime=clock();
//	extern __int64 StartTime;
//	extern double Frequency;
//	StartTime = -1;
//	Frequency = -1;
	Kernel::Time();

	extern HANDLE Win_Console;
	Win_Console = con;
	extern Process *ThisProcess;
	ThisProcess = proc;
//	printf("Process %x started\n",proc);

//	return new Meteorites();
	extern int ActiveDriver;
	ActiveDriver = adrv;

	extern DynamicArray *Entries;
	Entries = Input;
	//Entries = new DynamicArray();
	//int cnt = Input->GetCount();
	//for(int n=0; n<cnt; n++) Entries->Add(Input->GetItem(n));

extern bool Initialized;
	Initialized = false;

	ThreadArgs args={0,0}; //argc,argv};
	DWORD dwThreadID = 0;
void ProcessThread(ThreadArgs *a);
	HANDLE hThread = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)ProcessThread,
		&args,
		0,
		&dwThreadID);

#if 0

//	extern HANDLE APCHandle;
//	APCHandle = CreateThread(
//		NULL,
//		0,
//		(LPTHREAD_START_ROUTINE)APCThread,
//		0,
//		0,
//		&dwThreadID);

	CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)MessageThread,
		proc,
		0,
		&dwThreadID);

#endif
while(!Initialized){
	Sleep(500);
}

	return 0;
}

//__declspec(dllexport) void Destructor(void *ptr){
//	Meteorites *scr = (Meteorites*)ptr;
//	delete scr;
//}

