
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include <posix/stdio.h>
#include <posix/string.h>
#include <Interface/Font.h>
#include <Interface/View.h>
#include <Interface/DynamicArray.h>
#include <Interface/Bitmap.h>
#include <Interface/Garbage.h>
#include "TextView.h"

class Transition{
public:		Transition(View *, char *, DynamicArray *images);
			~Transition();
	bool	Tick(double);
private:
	double	start_t;
	float	in,idle,out;
	View	*view;
//	Font	*font;
	int		effect;
	float	row,Width;
};

Font	*font = 0;

static void GarbageCollector(void){
	if(font) delete font;
}

Transition::Transition(View *parent, char *text, DynamicArray *images){
	float val,time;
	int f = sscanf(text,"%f%f%d",&val,&time,&effect);
	while(f--) while(*text++!=',');
	if(!font){	// fixme: We need some propper font caching
		font = new Font("Fonts/swed");//Humnst777_BT_40"); //swiss");   //arial15pt1");
		font->SetSize(.05f);
	}
//printf(".................. %f\n",Width);
	switch(effect){
	case 1:{
		view = new View(Rect(1,val,1+Width,val+.04f));
		view->/*ConsoleStream::*/Apply(font);
		view->SetClearState(false);
		view->ConsoleStream::Clear();
		view->SetColor(ARGB(.7f,.7f,.7f));
		int f = sscanf(text,"%f%f%f",&in,&idle,&out);
		while(f--) while(*text++!=',');

		int len = 0;
		char *str = text;
		while(*str){
			while(*str==0x1){
				*str = 0;
				float w = font->GetWidth(text);
				*str = 1;
//				View *v = new View(Rect(w,0,w+.01f,1));
//				view->Apply(new Bitmap("Textures/interface/playernum/no1",Bitmap::cARGB)); // fixme: Crash bug!
//				view->Apply(v);
				str+=2;
			}
			len++;
			str++;
		}
		str = text;
		char *string = new char[len+1];
		char *dst = string;
		for(int n=0; n<len; n++){
			while(*str==0x1) str+=2;
			*dst++=*str++;
		}
		*dst = 0;

		Width = font->GetWidth(string);
		start_t = -1;
		idle+=in;
		out+=idle;
//printf("%f,%f,%f,%s\n",in,idle,out,text);
		view->Print(string);
		delete string;
	}break;
	case 2:
	case 3:{
		view = new View(Rect(.5f-Width*.5f,val,.5f+Width*.5f,val+.04f));
		view->/*ConsoleStream::*/Apply(font);
		view->SetClearState(false);
		view->ConsoleStream::Clear();
		view->SetColor(ARGB(1,1,1));
		// Fade in, fade out
		int f = sscanf(text,"%f%f%f",&in,&idle,&out);
		while(f--) while(*text++!=',');
		Width = font->GetWidth(text);
		start_t = -1;
		idle+=in;
		out+=idle;
//printf("%f,%f,%f,%s\n",in,idle,out,text);
		view->Print(text);
	}break;
	default:
		printf("Warning: Illegal transition effect!\n");
	}
row = val;
	parent->Apply(view);
}
Transition::~Transition(){
//printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//	delete font;
	delete view;
}
bool Transition::Tick(double time){
	if(start_t<0) start_t = time;
	switch(effect){
	case 1:
		time-=start_t;
//if(time>out) return false;
		view->Set(Rect(1-time*.1f,row,1+Width-time*.1f,row+.04f));
		if((1+Width-time*.1f)<0) start_t+=time; //return false;
	break;
	case 2:
	case 3:
		time-=start_t;
		if(time>out) return false;
		else if(time>idle) view->SetTransparency(time*(idle-in));
		else if(time>in) view->SetTransparency(0);
		else view->SetTransparency(1.0f-time*in);
	break;
	}
	return true;
}



TextView::TextView(View *_parent) : Message(){
	AddGarbageCollector(GarbageCollector);

	SetName("ScrollText");

	parent = _parent;
#if 0
	sprintf(testText,
		// vertical position,delay until next effect,effect,[effect parameters...,]text...
		".93,100,1,1,100,1,"
		"!\"#$%&'()*+,-/0123456789∆∆∆∆∆ÿÿÿÿ≈≈≈≈≈ÊÊÊÊ¯¯¯¯ÂÂÂThe purpose of this paper \x1\x1 is to discuss interprocess communication in the context of Berkeley UNIX. Special "
		"emphasis will be given to those system calls concerned with the creation, management, and use of sockets. There "
		"will also be a discussion of signals and selected other system calls that will be useful to those working on the net- "
		"work project assigned for this course. More information on all the system calls mentioned below can be found in "
		"the UNIX Programmer's Manual. Periodic mention will be made of other manual page entries that might be con- "
		"sulted. System header files are designated by enclosing angle brackets; they reside in /usr/include and its subdirec- "
		"tories. "
/*		"1. Socket Creation "
		"The most general mechanism for interprocess communication offered by Berkeley UNIX is the socket. A "
		"socket is an endpoint for communication. Two processes can communicate by creating sockets and sending mes- "
		"sages between them. There are a variety of different types of sockets, differing in the way the address space of the "
		"sockets is defined and the kind of communication that is allowed between sockets. A socket type is uniquely deter- "
		"mined by a <domain, type, protocol> triple. In order for a remote socket to be reached, it must be possible to assign "
		"a name to it. The form that this name assumes is determined by the communication domain or address family to "
		"which the socket belongs. There is also an abstract type or style of communication associated with each socket. "
		"This dictates the semantics of communication for that socket. Finally, there is a specific protocol that is used with "
		"the socket. A socket can be created with the socket system call by specifying the desired address family, socket "
		"type, and protocol. "
		"socket_descriptor = socket(domain, type, protocol) "
		"int socket_descriptor, domain, type, protocol; "
		"This call returns a small positive integer called a socket descriptor that can be used as a parameter to reference the "
		"socket in subsequent system calls. Socket descriptors are similar to file descriptors returned by the open system call. "
		"Each open or socket call will return the smallest unused integer. Thus a given number denotes either an open file, a "
		"socket, or neither (but never both). Socket and file descriptors may be used interchangeably in many system calls. "
		"For example, the close system call is used to destroy sockets. "
		"1.1. Domains "
		"The communication domain or address family to which a socket belongs specifies a certain address format. "
		"All later operations on a socket will interpret the supplied address according to this specified format. The various "
		"address formats are defined as manifest constants in the file <sys/socket.h>. 1 Examples are AF_UNIX (UNIX path "
		"names), AF_INET (DARPA Internet addresses), and AF_OSI (as specified by the international standards for Open "
*/		"Systems Interconnection). AF_UNIX and AF_INET are the most important address families. The general form of\n"
//		".88,2,2,1,1,1,svada text\n"
//		".91,2,3,1,1,1,mer svada text\n"
		);
	int len = strlen(testText);
	for(int n=0; n<len; n++) if(testText[n]=='\n') testText[n]='\0';
#endif
/*
	view = new View(Rect(0,.9f,1,1));
	view->ConsoleStream::Apply(font);
	view->SetClearState(false);
	view->ConsoleStream::Clear();
*/
//	text->Print("dette er en test. masse tekst med bare tull"); //\nher kommer det noen effekter snart");

//	view->Print(testText);
//	text=testText+strlen(testText)+1;
	text = 0; //testText;
	textptr = 0;
	t_start = -1.0f;
	delay = 5;

//	view->SetColor(ARGB(1,1,1));
//	parent->Apply(view);
	Transitions = new DynamicArray();

	images = new DynamicArray();
//	images->Add(new Bitmap("Textures/interface/playernum/no1",Bitmap::cARGB));
}

TextView::~TextView(){
	if(text) delete text;
	int cnt = images->GetCount();
	for(int n=0; n<cnt; n++) delete (Bitmap*)images->GetItem(n);
	delete images;
	cnt = Transitions->GetCount();
	for(n=0; n<cnt; n++) delete (Transition*)(Transitions->GetItem(n));
	delete Transitions;
}

void TextView::Tick(double time){
	if(textptr){
		if(t_start<0) t_start = time;
		if(time-t_start>delay){
			t_start+=delay;
			//view->ConsoleStream::Clear();
			//view->Print(text);
			float f;
			sscanf(textptr,"%f%f",&f,&delay);
			#ifdef _DEBUG
			Transitions->Add(new Transition(parent,textptr,images),__FILE__,__LINE__);
			#else
			Transitions->Add(new Transition(parent,textptr,images));
			#endif
			textptr+=strlen(textptr)+1;
			if(textptr[0]=='\0') textptr=0; //text; //testText;
		}
	}
	int cnt = Transitions->GetCount();
	for(int n=0; n<cnt; n++){
		Transition *t = (Transition*)Transitions->GetItem(n);
		if(!t->Tick(time)){
			cnt--;
			#ifdef _DEBUG
			Transitions->Remove(n--,__FILE__,__LINE__);
			#else
			Transitions->Remove(n--);
			#endif
			delete t;
		}
	}
}

void TextView::MessageReceived(void){

	while(Transitions->GetCount()){
		Transition *t = (Transition*)Transitions->GetItem(0);
		#ifdef _DEBUG
		Transitions->Remove(0,__FILE__,__LINE__);
		#else
		Transitions->Remove(0);
		#endif
		delete t;
	}

//	printf("Scroll text received!\n");
	char str[] = ".93,10,1,1,10,1,";
//	char str[] = ".93,500,1,1,500,1,";
	int slen = strlen(str);
	char *buf = (char*)GetReceivedBuffer();
	int len = *(int16*)buf; buf = (char*)(int(buf)+sizeof(int16));
	if(text) delete text;
	text = new char[strlen(str)+len+2];
	sprintf(text,str);
	for(int n=0; n<len; n++) text[n+slen] = *buf++;
	text[len+slen]=0;
	text[len+slen+1]=0;
	textptr = text;
}

