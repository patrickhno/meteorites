
#define TV2
//#define SCHIBSTED
//#define JANCO

// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

//#define rand foo
//#include <posix/stdio.h>

#include <windows.h>
#define INTERNAL_DEFINES

#include "Meteorites.h"
#include <Interface/DynamicArray.h>
#include "Geometry.h"
#include "IndexedPolygon.h"
#include "RockAI.h"
#include <Interface/View.h>
#include <Interface/Bitmap.h>
#include "Texture.h"
#include "Material.h"
#include "Background.h"
#include "Player.h"
#include "Camera.h"
#include "CameraAI.h"
#include "Host.h"
#include <Interface/WindowScreen.h>
#include <Interface/Font.h>
#include "GameServer.h"
#include "Planet.h"
#include "Sun.h"
#include "Nebula.h"

#include <posix/stdlib.h>
#include <posix/time.h>
#include <Interface/String.h>
#include "ScoreViews.h"
#include <posix/unistd.h>
//#include <posix/time.h>

#include "Scene.h"
#include "TextView.h"
#include "PhoneNumber.h"

//#undef rand
//#undef abs
//#include <windows.h>
//#include "GameDLL.h"

//#include "Debug.h"

//printf_func my_printf;
/*
int printf(const char *fmt,...){
	char str[1024];
	va_list	args;
	va_start(args,fmt);
	vsprintf(str,fmt,args);
	my_printf("%s",str);
	return 0;
}
*/
class ConsoleProgressBar{
public:		ConsoleProgressBar(int width, int progressticks);
			~ConsoleProgressBar();
	void	Tick(void);
private:
	int		width;
	int		progress;
	int		last;
	int		maxprogress;
};

ConsoleProgressBar::ConsoleProgressBar(int _width, int progressticks){
	width = _width-2;
	printf("\r[");
	for(int n=0; n<width; n++) printf("-");
	printf("]\r");
	int last=0;
	maxprogress = progressticks;
	progress=0;
}

ConsoleProgressBar::~ConsoleProgressBar(){
	width+=2;
	for(int n=0; n<width; n++) printf(" ");
	printf("\r");
}

void ConsoleProgressBar::Tick(void){
	progress++;
	int n = (progress*width)/maxprogress;
//printf("%d/%d,%d\n",progress,maxprogress,n);
	if(n>last){
		last = n;
		printf("[");
		for(int n=0; n<last; n++) printf("#");
		printf("\r");
	}
}

//--------------

bool	Initialized;

Meteorites::Meteorites() : /*Client(),*/ Message(){

	msg = new Message();
	scr = 0;

	ViewBunch = new DynamicArray();
	BitmapBunch = new DynamicArray();

	SetName("MeteoritesGame");

	printf("------------------------------------------------------------------------\n");
	printf("  TV-Meteorites, Copyright (C) 1997-1998 RealityMakers Entertainment as\n");
	printf("------------------------------------------------------------------------\n");
	View1 = new View(Rect(0,0,1,1));
//	View1->SetClearState(false);	// @@@@@@@@@@@@@@

/*
	Scores = new ScoreViews(View1);
*/
//	191,189
//	101
//	85
/*
	#ifdef TV2
	tv2bm = new Bitmap("Textures/tv2/tv2",Bitmap::cRGB);
	tv2v  = new View(Rect(
		1-.075f*.8f-.01f,
		  .01f,
		1-.01f,
		  .1f  *.8f+.01f));
	tv2bm->SetTranslusency(.5f);
	tv2v->Apply(tv2bm);
	tv2v->SetClearState(false);
	View1->Apply(tv2v);
	#endif
	#ifdef SCHIBSTED
	tv2bm = new Bitmap("Textures/tv2/slogo",Bitmap::cRGB);
	tv2v  = new View(Rect(
		1-.09f*.8f*1.5f-.01f,
		.01f,
		1-.01f,
		.1f*.8f+.01f));
	tv2bm->SetTranslusency(.5f);
	tv2v->Apply(tv2bm);
	tv2v->SetClearState(false);
	View1->Apply(tv2v);
	#endif
	#ifdef JANCO
	Bitmap *tv2bm = new Bitmap("Textures/tv2/janco",BITMAP_RGB);
	View *tv2v  = new View(Rect(
		.9f,
		0,
		1,
		.1f));
	tv2bm->SetTranslusency(.5f);
	tv2v->Apply(tv2bm);
	tv2v->SetClearState(false);
	View1->Apply(tv2v);
	#endif
*/
//printf("Meteorites::Meteorites():a\n");
//	Info1 = new Bitmap("Textures/Interface/Instructions/Inntasting",Bitmap::cRGB);
//	Info2 = new Bitmap("Textures/Interface/Instructions/Kontroll",Bitmap::cRGB);
//	Info3 = new Bitmap("Textures/Interface/Instructions/Pickups",Bitmap::cRGB);
//printf("%d,%d\n",Info1->GetWidth(),Info1->GetHeight());
//printf("%d,%d\n",Info2->GetWidth(),Info2->GetHeight());
//printf("%d,%d\n",Info3->GetWidth(),Info3->GetHeight());
//	View *InfoView = new View(Rect(.75f,.7f,.95f,.9f));
//	InfoView->SetClearState(false);
//	View *v1 = new View(Rect(0,0,1,1.3f));
//	View *v2 = new View(Rect(0,0,1,101.0f/189.0f*1.3f));
//	View *v3 = new View(Rect(0,0,1,85.0f/189.0f*1.3f));
//	InfoViews = new DynamicArray();
//	#ifdef _DEBUG
//	InfoViews->Add(InfoView,__FILE__,__LINE__);
//	InfoViews->Add(v1,__FILE__,__LINE__);
//	InfoViews->Add(v2,__FILE__,__LINE__);
//	InfoViews->Add(v3,__FILE__,__LINE__);
//	#else
//	InfoViews->Add(InfoView);
//	InfoViews->Add(v1);
//	InfoViews->Add(v2);
//	InfoViews->Add(v3);
//	#endif
//	v1->Apply(Info1);
//	v2->Apply(Info2);
//	v3->Apply(Info3);
//	v1->SetClearState(false);
//	v2->SetClearState(false);
//	v3->SetClearState(false);
//	InfoView->Apply(v1);
//	InfoView->Apply(v2);
//	InfoView->Apply(v3);
//	View1->Apply(InfoView);
//printf("Meteorites::Meteorites():b\n");


//	Info3->SetTranslusency(.8f);

//	pnum = new PhoneNumber(View1);

#if 1
	null = new Geometry();
	null->SetPosition(0,Vector(0,0,10000));
	scene = new Scene(null,View1);
//	Text = new TextView(View1);
//printf("Meteorites::Meteorites():c\n");
#else
	Scores = new ScoreViews(View1);

	null = new Geometry();
	null->SetPosition(Vector(0,0,10000));

	Back = new Geometry();
	Back->Node::Apply(new Background(Back));
	Back->SetPosition(Vector(0,0,8000*3));
	Back->Post();
	null->Node::Apply(Back);

	new Nebula(null);
	new	Sun(null);
//	new Planet(null);

	cam = new Camera();
	cam->SetName(String("Camera"));
	null->Node::Apply(cam);
	camAI = new CameraAI(cam);
	cam->Apply(camAI);
	View1->Attatch(cam);
/*
//	PlayerGeometries = new DynamicArray();
	for(int n=0; n<16; n++){
		Geometry *Ship = new Geometry();
		char name[1024];
		sprintf(name,"Player%d",n);
		Ship->SetName(String(name));	// fixme: Optimize!
		//Ship->SetPosition(Vector(0,0,-800000));
		Ship->Post();
//		PlayerGeometries->Add(Ship);
		//AI_Player1 = new PlayerAI(Ship);
		null->Node::Apply(Ship);
		Ship->Node::Apply(new PlayerAI(Ship,Scores,Scores->GetPlayer(n),0));
	}
*/
//#if 0
	for(int n=0; n<10; n++){
		Geometry *Rock = new Geometry();
		Rock->SetName("Rock");
		Rock->Add(Vector(-400,-400,0));
		Rock->Add(Vector( 400,-400,0));
		Rock->Add(Vector( 400, 400,0));
		Rock->Add(Vector(-400, 400,0));
		Rock->Add(Vertex(0,0,0));
		Rock->Add(Vertex(1,1,0));
		Rock->Add(Vertex(2,1,1));
		Rock->Add(Vertex(3,0,1));
		IndexedPolygon *pol = Rock->NewIndexedPolygon();
		pol->Add(0);
		pol->Add(1);
		pol->Add(2);
		pol->Add(3);
		RockAI *AI_Rock = new RockAI(/*this,*/Rock,400.0f);
		Rock->Node::Apply(AI_Rock);
		null->Node::Apply(Rock);
	}
//#endif
	//
#if 0
	printf("Initializing levels.\n");
	//#ifndef _DEBUG
	InitLevels(2);
	NextLevel(10);
	//#endif
	printf("Done.\n");
#endif
#endif
	printf("------------------------------------------------------------------------\n");
	printf("                       TV-Meteorites initalized\n");
	printf("------------------------------------------------------------------------\n");

//extern void win32_Reboot(void);
//win32_Reboot();

	Initialized = true;
}

Meteorites::~Meteorites(){

	delete pnum;

#ifdef TV2
	delete tv2v;
	delete tv2bm;
#endif
#ifdef SCHIBSTED
	delete tv2v;
	delete tv2bm;
#endif

#if 0
	delete PlayerGeometries;
	delete ScoreView;
	delete View4;
	delete MeteoritesBitmap;

//	delete View2;

#endif
	delete Scores;
//	delete Text;
	int cnt = ViewBunch->GetCount();
	for(int n=0; n<cnt; n++) delete (View*)ViewBunch->GetItem(n);
	delete ViewBunch;
	cnt = BitmapBunch->GetCount();
	for(n=0; n<cnt; n++) delete (Bitmap*)BitmapBunch->GetItem(n);
	delete BitmapBunch;
//	delete ScoreViews;
	delete font;
//	delete Info1;
//	delete Info2;
//	delete Info3;
//	cnt = InfoViews->GetCount();
//	for(n=0; n<cnt; n++) delete (View*)InfoViews->GetItem(n);
//	delete InfoViews;
//	null->DoKill();
	delete null;
	delete View1;	// fixme: Parent view is fucked up!
	delete msg;
}

void Meteorites::MessageLoop(void){
	quit = false;
	//int tr=0;
	while(!quit||!allowquit){
		sleep(1);
		//Info3->SetTranslusency(float(tr++&0xff)/255.0f);
	}
	printf("Leaving message loop. %d,%d\n",quit,allowquit);
}

void Meteorites::Refresh(WindowScreen *scr){
	int t=int(float(clock())*(1.0f/CLOCKS_PER_SEC)*256.0f);
	//printf("%d\n",tr);
	//tr&=0x3ff;
	//if(tr&0x3ff<=0xff) Info1->SetTranslusency(float(tr&0xff)/255.0f);
	//else Info1->SetTranslusency(1.0f);
	//if(tr&0x3ff>0xff&&tr&0x3ff<=0x1ff) Info2->SetTranslusency(float((tr>>1)&0xff)/255.0f);
	//else Info2->SetTranslusency(1.0f);
//#if 0
/*
	t/=2;
	t=t%0xc00;

	if(t<0x100) Info3->SetTranslusency(float(t&0xff)/255.0f);

	if(t<0x500){
		int tr = t;
		if(tr<0x100) Info1->SetTranslusency(1.0f-float(tr&0xff)/255.0f);
		else if(tr>=0x100&&tr<0x400) Info1->SetTranslusency(0);
		else if(tr>=0x400) Info1->SetTranslusency(float(tr&0xff)/255.0f);
	}else Info1->SetTranslusency(1.0f);

	t-=0x400;
	if(t>=0&&t<0x500){
		int tr = t;
		if(tr<0x100) Info2->SetTranslusency(1.0f-float(tr&0xff)/255.0f);
		else if(tr>=0x100&&tr<0x400) Info2->SetTranslusency(0);
		else if(tr>=0x400) Info2->SetTranslusency(float(tr&0xff)/255.0f);
	}else Info2->SetTranslusency(1.0f);

	t-=0x400;
	if(t>=0&&t<0x500){
		int tr = t;
		if(tr<0x100) Info3->SetTranslusency(1.0f-float(tr&0xff)/255.0f);
		else if(tr>=0x100&&tr<0x400) Info3->SetTranslusency(0);
		//else if(tr>=0x400) Info3->SetTranslusency(float(tr&0xff)/255.0f);
	}else if((t+0x800)>=0x100) Info3->SetTranslusency(1.0f);
*/
//#endif
	scr->Refresh();
}

struct RefreshArgs{
	WindowScreen	*scr;
	Meteorites		*game;
	bool			bailout;
};
/*
void RefreshThread(RefreshArgs *args){
	while(!args->bailout) args->game->Refresh(args->scr);
	args->bailout = false;
}
*/

#include <Interface/Thread.h>

class RefreshThread : Thread{
public:		RefreshThread(WindowScreen *scr, Meteorites *game);
			~RefreshThread();
void		main(void);
private:
	WindowScreen	*scr;
	Meteorites		*game;
};

RefreshThread::RefreshThread(WindowScreen *_scr, Meteorites *_game) : Thread(){
	scr = _scr;
	game = _game;
}

RefreshThread::~RefreshThread(){
}

#ifndef _DEBUG
//#define FIREMAN
//#include <Fireman/Fireman.h>
//#include <3dapi/Network/Socket.h>
#endif

//bool ping_fireman;

void RefreshThread::main(void){
	printf("RefreshThread:a\n");
	#ifdef FIREMAN
	int proc = GetCurrentProcessId();
	printf("RefreshThread:b\n");
	Message *msg = new Message(new Socket("localhost:50001"));
	printf("RefreshThread:c\n");
	msg->AddPacket(Fireman::SAVE_ME);
	printf("RefreshThread:d\n");
	msg->Add((int32)proc);
	printf("RefreshThread:e\n");
	msg->Send();
	printf("RefreshThread:f\n");
	ping_fireman = true;
	double ping_time = Kernel::Time();
	#endif
	printf("Entering game loop!\n");
	while(!game->bailout){
		#ifdef FIREMAN
		if(ping_fireman){
			double ping = Kernel::Time();
			if(ping-ping_time>5.0f){
				ping_time = ping;
				msg->AddPacket(Fireman::PULSE);
				msg->Add((int32)proc);
				msg->Send();
			}
//ping_fireman = false;
		}
		#endif
		game->Refresh(scr);
	}
	printf("Leaving game loop!\n");
	#ifdef FIREMAN
	msg->AddPacket(Fireman::LEAVE_ME);
	msg->Add((int32)proc);
	msg->Send();
	delete msg;
	#endif
	game->bailout = false;
}

/*
void Meteorites::MessageReceived(double time, int Cmd, void *data){
	//printf("Received a message\n");
	if(Cmd==AttatchHook){
		printf("Received a Attatch message\n");
		WindowScreen *scr = (WindowScreen*)data;
#if 1
		scr->SetClearState(false);
		scr->Apply(View1);

		rfargs = new RefreshArgs;
		rfargs->scr = scr;
		rfargs->bailout = false;

		DWORD dwThreadID;
		CreateThread(
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)RefreshThread,
			rfargs,
			0,
			&dwThreadID);

#else
		scr->SetClearState(false);
		scr->Apply(View1);
//		scr->Apply(View2);
//		scr->Apply(View4);
while(true){
	ScoreView->ConsoleStream::Clear();
	ScoreView->Print(" 1: %d\n",rand());
	ScoreView->Print(" 2: %d\n",rand());
	ScoreView->Print(" 3: %d\n",rand());
	ScoreView->Print(" 4: %d\n",rand());
	ScoreView->Print(" 5: %d\n",rand());
	ScoreView->Print(" 6: %d\n",rand());
	ScoreView->Print(" 7: %d\n",rand());
	ScoreView->Print(" 8: %d\n",rand());
	ScoreView->Print(" 9: %d\n",rand());
	ScoreView->Print("10: %d\n",rand());
	ScoreView->Print("11: %d\n",rand());
	ScoreView->Print("12: %d\n",rand());
	ScoreView->Print("13: %d\n",rand());
	ScoreView->Print("14: %d\n",rand());
	ScoreView->Print("15: %d\n",rand());
	ScoreView->Print("16: %d\n",rand());

		scr->Refresh();
		scr->Refresh();
		scr->Refresh();
		scr->Refresh();
		scr->Refresh();
		scr->Refresh();
}
#endif

//quit=true;
	}else if(Cmd==DetatchHook){
		printf("Received a Detatch message\n");
		rfargs->bailout = true;
		while(rfargs->bailout) Sleep(500);
		delete rfargs;
quit = true;
	}else if(Cmd==ShutDownHook){
		quit=true;
	}
}
*/

#include <Interface/Garbage.h>

void Meteorites::MessageReceived(void){
	int cnt = GetReceivedCount();
	char *buf = (char*)GetReceivedBuffer();
	for(int n=0; n<cnt; n++){
		switch(GetReceivedCommand(n)){
		case GAME_INITIALIZE:
			printf("GAME_INITIALIZE\n");
		break;
		case GAME_SHUTDOWN:
			printf("GAME_SHUTDOWN\n");
			quit=true;
		break;
		case GAME_START:{
			allowquit=false;
			printf("GAME_START:a\n");
			float scale;
			float maxtime;//,zoom;
			int32 maxplayers,s;
			Get(s);
			Get(maxtime);
			Get(maxplayers);
			Get(scale);

//extern float dialogic_max_time;
//extern int dialogic_max_players;
//dialogic_max_time = maxtime;
if(maxplayers>30) maxplayers = 30;
if(maxplayers<0) maxplayers = 0;
//dialogic_max_players = maxplayers;

	msg->Add(maxplayers);
	msg->Add(maxtime);
	msg->SendTo("/Devices/Input/Dialogic");

//			Get(zoom);
//printf("%f,%d,%f\n",maxtime,maxplayers,zoom);

//			Add(zoom);
//			SendTo("/Devices/Glide");
//			msg->Add(zoom);
//			msg->SendTo("/Devices/Glide");

			printf("GAME_START:b\n");
//			if(!scr) scr = new WindowScreen();
			scr = (WindowScreen*)s;
			scr->SetScale(scale);
			scr->SetClearState(false);
			scr->Apply(View1);

			printf("GAME_START:c\n");
			//rfargs = new RefreshArgs;
			bailout = false;
/*
			rfargs->scr = scr;
			rfargs->game = this;

			DWORD dwThreadID;
			CreateThread(
				NULL,
				0,
				(LPTHREAD_START_ROUTINE)RefreshThread,
				rfargs,
				0,
				&dwThreadID);
*/
			Leftover(new RefreshThread(scr,this));
			printf("GAME_START:d(%x)\n",scr);
		}break;
		case GAME_STOP:
			printf("GAME_STOP\n");
printf("GAME_STOP:a (%x)\n",scr);
			scr->Detatch(View1);	// fixme: Crashes in GameServer
printf("GAME_STOP:b\n");
			bailout = true;
printf("GAME_STOP:c\n");
//			while(bailout) sleep(100);
printf("GAME_STOP:d\n");
//			if(scr) delete scr;
//			scr = 0;
			//delete rfargs;
printf("GAME_STOP:e\n");
			allowquit=true;
printf("GAME_STOP:f\n");
		break;
		//case PROPERTIES;
		//	Get(buf,len);
		//break;
		}
	}
}

void main(int,char**){
	Message *msg = new Message();
	Meteorites *game = new Meteorites();
	#ifndef _DEBUG
	msg->AddPacket(1);
	msg->SendTo("LogCollector");
	#endif
	game->MessageLoop();
	printf("Deleting game\n");
	delete game;
	printf("Leaving\n");
	delete msg;
}

