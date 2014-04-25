
//#define TV2
//#define SCHIBSTED
//#define JANCO

// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

//#define rand foo
#include <posix/stdio.h>
#include "Meteorites.h"
#include <Interface/DynamicArray.h>
#include <3dapi/Geometry.h>
#include <3dapi/IndexedPolygon.h>
#include "RockAI.h"
#include <Interface/View.h>
#include <Interface/Bitmap.h>
#include <3dapi/Texture.h>
#include <3dapi/Material.h>
#include "Background.h"
#include "Player.h"
#include <3dapi/Camera.h>
#include "CameraAI.h"
//#include "Host.h"
#include <Interface/WindowScreen.h>
#include <Interface/Font.h>
#include <GameServer/GameServer.h>
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

Meteorites::Meteorites() : Client(), Message(){

	ViewBunch = new DynamicArray();
	BitmapBunch = new DynamicArray();

	SetName("MeteoritesGame");

	printf("------------------------------------------------------------------------\n");
	printf("Initializing TV-Meteorites, Copyright (C) RealityMakers Entertainment as\n");
	printf("------------------------------------------------------------------------\n");

	View1 = new View(Rect(0,0,1,1));
	View1->SetClearState(false);
/*
	Scores = new ScoreViews(View1);
*/
//	191,189
//	101
//	85

	#ifdef TV2
	tv2bm = new Bitmap("Textures/tv2/tv2",BITMAP_RGB);
	tv2v  = new View(Rect(
		1-.075f*.8f-.01f,
		.01f,
		1-.01f,
		.1f*.8f+.01f));
	tv2bm->SetTranslusency(.5f);
	tv2v->Apply(tv2bm);
	tv2v->SetClearState(false);
	View1->Apply(tv2v);
	#endif
	#ifdef SCHIBSTED
	tv2bm = new Bitmap("Textures/tv2/slogo",BITMAP_RGB);
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

	Info1 = new Bitmap("Textures/Interface/Instructions/Inntasting",BITMAP_RGB);
	Info2 = new Bitmap("Textures/Interface/Instructions/Kontroll",BITMAP_RGB);
	Info3 = new Bitmap("Textures/Interface/Instructions/Pickups",BITMAP_RGB);
//printf("%d,%d\n",Info1->GetWidth(),Info1->GetHeight());
//printf("%d,%d\n",Info2->GetWidth(),Info2->GetHeight());
//printf("%d,%d\n",Info3->GetWidth(),Info3->GetHeight());
	View *InfoView = new View(Rect(.75f,.7f,.95f,.9f));
	InfoView->SetClearState(false);
	View *v1 = new View(Rect(0,0,1,1.3f));
	View *v2 = new View(Rect(0,0,1,101.0f/189.0f*1.3f));
	View *v3 = new View(Rect(0,0,1,85.0f/189.0f*1.3f));
	InfoViews = new DynamicArray();
	InfoViews->Add(InfoView);
	InfoViews->Add(v1);
	InfoViews->Add(v2);
	InfoViews->Add(v3);
	v1->Apply(Info1);
	v2->Apply(Info2);
	v3->Apply(Info3);
	v1->SetClearState(false);
	v2->SetClearState(false);
	v3->SetClearState(false);
	InfoView->Apply(v1);
	InfoView->Apply(v2);
	InfoView->Apply(v3);
	View1->Apply(InfoView);


//	Info3->SetTranslusency(.8f);
#if 1
	scene = new Scene(View1);
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

	Initialized = true;
}

Meteorites::~Meteorites(){

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
	int cnt = ViewBunch->GetCount();
	for(int n=0; n<cnt; n++) delete (View*)ViewBunch->GetItem(n);
	delete ViewBunch;
	cnt = BitmapBunch->GetCount();
	for(n=0; n<cnt; n++) delete (Bitmap*)BitmapBunch->GetItem(n);
	delete BitmapBunch;
//	delete ScoreViews;
	delete font;
	delete Info1;
	delete Info2;
	delete Info3;
	cnt = InfoViews->GetCount();
	for(n=0; n<cnt; n++) delete (View*)InfoViews->GetItem(n);
	delete InfoViews;
//	null->DoKill();
	delete scene;
	delete View1;
}

void Meteorites::MessageLoop(void){
	WindowScreen *scr = new WindowScreen();
	scr->SetClearState(false);
	scr->Apply(View1);
	int n=1000;
	while(true){ //n-->0){
		Refresh(scr);
		scr->Refresh();
	}
	delete scr;
/*
	quit = false;
	//int tr=0;
	while(!quit||!allowquit){
		sleep(.5f);
		//Info3->SetTranslusency(float(tr++&0xff)/255.0f);
	}
	printf("Leaving message loop. %d,%d\n",quit,allowquit);
*/
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

void RefreshThread::main(void){
	while(!game->rfargs->bailout) game->Refresh(scr);
	game->rfargs->bailout = false;
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
			printf("GAME_START\n");
			int32 s;
			Get(s);
printf("%x\n",s);
			scr = (WindowScreen*)s;
			scr->SetClearState(false);
			scr->Apply(View1);

			rfargs = new RefreshArgs;
			rfargs->bailout = false;
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
		}break;
		case GAME_STOP:
			printf("GAME_STOP\n");
			scr->Detatch(View1);
			rfargs->bailout = true;
			while(rfargs->bailout) sleep(.5f);
			delete rfargs;
			allowquit=true;
		break;
		}
	}
}

#include <Devices/Input/PhoneDevice.h>

void main(int,char**){
	Phone *phone = new Phone();
	phone->CreateVirtual("/Devices/Input/Dialogic");
	Meteorites *game = new Meteorites();
	game->MessageLoop();
	printf("Deleting game\n");
	delete game;
	printf("Leaving\n");
}
#if 0
/**************************************************************\
|      Copyright (C) 1997 RealityMakers Entertainment AS       |
|                     All rights reserved.                     |
\**************************************************************/

#define rand foo
#include "Meteorites.h"
#include <Interface/DynamicArray.h>
#include <3dapi/Geometry.h>
#include <3dapi/IndexedPolygon.h>
#include "RockAI.h"
#include <Interface/View.h>
#include <Interface/Bitmap.h>
#include <3dapi/Texture.h>
#include <3dapi/Material.h>
#include "Background.h"
#include "Player.h"
#include <3dapi/Camera.h>
#include "CameraAI.h"
#include <3dapi/Network/Host.h>
#include <Interface/WindowScreen.h>
#include <Interface/Font.h>
#include "GameServer/GameServer.h"
#include "Planet.h"

#undef rand
#undef abs
#include <windows.h>
#include "GameDLL.h"

#include <Interface/Debug.h>
#include "ScoreViews.h"

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

Meteorites::Meteorites() : Client(), Message(){

	SetName("MeteoritesGame");

	printf("------------------------------------------------------------------------\n");
	printf("Initializing TV-Meteorites, Copyright (C) RealityMakers Entertainment as\n");
	printf("------------------------------------------------------------------------\n");

//	char *str = new char[strlen(GetCurrentProcess()->GetName())+];
//	SetName();

	extern Host *host;
//	AttatchHook  = host->CreateHook("Attatch");
//	DetatchHook  = host->CreateHook("Detatch");
//	ShutDownHook = host->CreateHook("ShutDown");

	View1 = new View(Rect(0,0,1,1));
	View1->SetClearState(false);

/*
	ScoreView = new View(Rect(.8f,0,1,.5f));
	ScoreView->SetClearState(false);
	ScoreView->ConsoleStream::Clear();
	ScoreView->Print(" 1: 1261\n 2: 8726\n");
	ScoreView->Print(" 3: 8145\n 4: 6923\n");
	ScoreView->Print(" 5: 1261\n 6: 8726\n");
	ScoreView->Print(" 7: 8145\n 8: 6923\n");
	ScoreView->Print(" 9: 1261\n10: 8726\n");
	ScoreView->Print("11: 8145\n12: 6923\n");
	ScoreView->Print("13: 1261\n14: 8726\n");
	ScoreView->Print("15: 8145\n16: 6923\n");
	font = new Font("Fonts/Swiss");
	ScoreView->ConsoleStream::Apply(font);
	View1->Apply(ScoreView);
*/
//	View2 = new View(Rect(.8f,0,1,.5f));
	View4 = new View(Rect(.75f,0,1,.8f));
//	View2->SetClearState(false);
//	View4->SetClearState(false);

//	MeteoritesBitmap = new Bitmap("Textures/interface/divider"/*Textures/Title/title"*/,BITMAP_RGB); //Titletv4");
//	View *LoadView = new View(Rect(.2f,.2f,1-.2f,1-.2f));
//	View4->Apply(MeteoritesBitmap);
//View1->Apply(View4);
	// Initialize scene

//	Bitmap *DividerBitmap = new Bitmap("Textures/interface/divider"/*Textures/Title/title"*/,BITMAP_RGB); //Titletv4");

	Bitmap *ShadowBM = new Bitmap("Textures/Interface/Shipshadow",BITMAP_ARGB);
	View *Shadow = new View(Rect(.7f,0,1,1));
//	View1->Apply(Shadow);

	ScoreViews = new DynamicArray();
	font = new Font("Fonts/Swiss");
	for(int n=0; n<4; n++){		// 12.5 x 23.3, 54.2 x 23.3
		#define xofs	.01f
		#define yofs	.1f
		#define width  (.233f*.8f)
		#define height (((.125f+.542f)/16.0f)*.8f)
		#define spacing ((0.1666667f/100.0f)*5.0f)

//		View *DividerView = new View(Rect(1-width,float(n)*height,1,float(n)*height+height-spacing));
//		DividerView->Apply(DividerBitmap);
//		DividerView->SetClearState(false);
//		View1->Apply(DividerView);

		char str[1024];
		sprintf(str,"Textures/interface/playernum/no%d",n+1);
		Bitmap *PlayerNBitmap = new Bitmap(str,BITMAP_RGB); //Titletv4");
		View *PlayerNView = new View(Rect(1-width-height+xofs,float(n)*height+yofs,1-width-spacing+xofs,float(n)*height+height-spacing+yofs));
		PlayerNView->Apply(PlayerNBitmap);
		PlayerNView->SetClearState(false);
		View1->Apply(PlayerNView);

		float scl = 1-width-height*2.0f+xofs;
		float sct = float(n)*height+yofs;
		float scr = 1-width-height+xofs;
		float scb = float(n)*height+height+yofs;
		float xs = (scr-scl)*.2f;
		float ys = (scb-sct)*.2f;
		scl+=xs;
		scr-=xs;
		sct+=ys;
		scb-=ys;
		switch(n){
		Bitmap *PlaceBitmap;
		View *PlaceView;
		case 0:
			PlaceBitmap = new Bitmap("Textures/interface/first",BITMAP_RGB); //Titletv4");
			PlaceView = new View(Rect(scl,sct,scr,scb));
			PlaceView->Apply(PlaceBitmap);
			PlaceView->SetClearState(false);
			View1->Apply(PlaceView);
		break;
		case 1:
			PlaceBitmap = new Bitmap("Textures/interface/second",BITMAP_RGB); //Titletv4");
			PlaceView = new View(Rect(scl,sct,scr,scb));
			PlaceView->Apply(PlaceBitmap);
			PlaceView->SetClearState(false);
			View1->Apply(PlaceView);
		break;
		case 2:
			PlaceBitmap = new Bitmap("Textures/interface/third",BITMAP_RGB); //Titletv4");
			PlaceView = new View(Rect(scl,sct,scr,scb));
			PlaceView->Apply(PlaceBitmap);
			PlaceView->SetClearState(false);
			View1->Apply(PlaceView);
		break;
		}

		#define fontscale  0
		View *v = new View(Rect(1-width+xofs,float(n)*height+fontscale+yofs,1+xofs,float(n)*height+height-spacing-fontscale+yofs));
		v->ConsoleStream::Apply(font);
		v->SetClearState(false);
		v->Print("0 ...");
		/*
		switch(n){
		case 0:  v->SetColor(ARGB(1,0,0)); break;
		case 1:  v->SetColor(ARGB(0,0,1)); break;
		case 2:  v->SetColor(ARGB(1,1,0)); break;
		case 3:  v->SetColor(ARGB(0,1,0)); break;
		case 4:  v->SetColor(ARGB(1,.5f,.5f)); break;
		case 5:  v->SetColor(ARGB(0,1,1)); break;
		case 6:  v->SetColor(ARGB(.5f,.5f,.5f)); break;
		case 7:  v->SetColor(ARGB(1,0,0)); break;
		case 8:  v->SetColor(ARGB(1,0,0)); break;
		case 9:  v->SetColor(ARGB(1,0,0)); break;
		case 10: v->SetColor(ARGB(1,0,0)); break;
		case 11: v->SetColor(ARGB(1,0,0)); break;
		case 12: v->SetColor(ARGB(1,0,0)); break;
		case 13: v->SetColor(ARGB(1,0,0)); break;
		case 14: v->SetColor(ARGB(1,0,0)); break;
		case 15: v->SetColor(ARGB(1,0,0)); break;
		}
		*/
		v->SetColor(ARGB(1,1,1));
		View1->Apply(v);
		ScoreViews->Add(v);
	}

//	191,189
//	101
//	85

	Info1 = new Bitmap("Textures/Interface/Instructions/Inntasting",BITMAP_RGB);
	Info2 = new Bitmap("Textures/Interface/Instructions/Kontroll",BITMAP_RGB);
	Info3 = new Bitmap("Textures/Interface/Instructions/Pickups",BITMAP_RGB);
printf("%d,%d\n",Info1->GetWidth(),Info1->GetHeight());
printf("%d,%d\n",Info2->GetWidth(),Info2->GetHeight());
printf("%d,%d\n",Info3->GetWidth(),Info3->GetHeight());
	View *InfoView = new View(Rect(.75f,.7f,.95f,.9f));
	InfoView->SetClearState(false);
	View *v1 = new View(Rect(0,0,1,1.3f));
	View *v2 = new View(Rect(0,0,1,101.0f/189.0f*1.3f));
	View *v3 = new View(Rect(0,0,1,85.0f/189.0f*1.3f));
	v1->Apply(Info1);
	v2->Apply(Info2);
	v3->Apply(Info3);
	v1->SetClearState(false);
	v2->SetClearState(false);
	v3->SetClearState(false);
	InfoView->Apply(v1);
	InfoView->Apply(v2);
	InfoView->Apply(v3);
	View1->Apply(InfoView);

	Info3->SetTranslusency(.8f);

	null = new Geometry();
	null->SetPosition(Vector(0,0,1000000));

	Back = new Geometry();
	Back->Node::Apply(new Background(Back));
	Back->SetPosition(Vector(0,0,800000));
	Back->Post();
	null->Node::Apply(Back);

	new Planet(null);

	cam = new Camera();
	cam->SetName("Camera");
	null->Node::Apply(cam);
	camAI = new CameraAI(cam);
	cam->Apply(camAI);

	View1->Attatch(cam);

	PlayerGeometries = new DynamicArray();
	for(n=0; n<4; n++){
		Geometry *Ship = new Geometry();
		char name[1024];
		sprintf(name,"Player%d",n);
		Ship->SetName(name);
		//Ship->SetPosition(Vector(0,0,-800000));
		Ship->Post();
		PlayerGeometries->Add(Ship);
		//AI_Player1 = new PlayerAI(Ship);
		null->Node::Apply(Ship);
		Ship->Node::Apply(new PlayerAI(Ship,(View*)ScoreViews->GetItem(n)));
	}

	//

	printf("Initializing levels.\n");
	//#ifndef _DEBUG
	InitLevels(2);
	NextLevel(10);
	//#endif
	printf("Done.\n");

	printf("------------------------------------------------------------------------\n");
	printf("                       TV-Meteorites initalized\n");
	printf("------------------------------------------------------------------------\n");

	Initialized = true;
}

Meteorites::~Meteorites(){
	delete View1;
	delete PlayerGeometries;
	delete ScoreView;
	delete font;
	delete View4;
	delete MeteoritesBitmap;
/*
	delete View2;
*/
	null->Kill();
}

void Meteorites::InitLevels(int count){
	Rocks = new DynamicArray();
	Rocks_sub = new DynamicArray();
	Rocks_sub_sub = new DynamicArray();
	AI_Rocks = new DynamicArray();
	Rocks_sub_item = 0;
	Rocks_sub_sub_item = 0;
	RockCount = 0;

	printf("Creating rocks...\n");
	int rCount = 10*count;
	ConsoleProgressBar *bar = new ConsoleProgressBar(40,rCount+rCount*3+rCount*3*3);
	for(int n=0; n<rCount; n++){
		Geometry *Rock = new Geometry();
		Rock->SetName("Rock");
/*
		Rock->Add(Vector(-40000,-40000,0));
		Rock->Add(Vector( 40000,-40000,0));
		Rock->Add(Vector( 40000, 40000,0));
		Rock->Add(Vector(-40000, 40000,0));
		Rock->Add(Vertex(0,0,0));
		Rock->Add(Vertex(1,1,0));
		Rock->Add(Vertex(2,1,1));
		Rock->Add(Vertex(3,0,1));
		IndexedPolygon *pol = Rock->NewIndexedPolygon();
		pol->Add(0);
		pol->Add(1);
		pol->Add(2);
		pol->Add(3);
*/
		Rocks->Add(Rock);
		RockAI *AI_Rock = new RockAI(this,Rock,40000.0f);
		Rock->Node::Apply(AI_Rock);
//		AI_Rocks->Add(AI_Rock);
		bar->Tick();
	}
/*
	for(n=0; n<rCount*3; n++){
		Geometry *Rock = new Geometry();
		Rock->SetName("Rock_sub");
		Rock->Add(Vector(-20000,-20000,0));
		Rock->Add(Vector( 20000,-20000,0));
		Rock->Add(Vector( 20000, 20000,0));
		Rock->Add(Vector(-20000, 20000,0));
		Rock->Add(Vertex(0,0,0));
		Rock->Add(Vertex(1,1,0));
		Rock->Add(Vertex(2,1,1));
		Rock->Add(Vertex(3,0,1));
		IndexedPolygon *pol = Rock->NewIndexedPolygon();
		pol->Add(0);
		pol->Add(1);
		pol->Add(2);
		pol->Add(3);
		Rocks_sub->Add(Rock);
		bar->Tick();
	}
	for(n=0; n<rCount*3*3; n++){
		Geometry *Rock = new Geometry();
		Rock->SetName("Rock_sub_sub");
		Rock->Add(Vector(-10000,-10000,0));
		Rock->Add(Vector( 10000,-10000,0));
		Rock->Add(Vector( 10000, 10000,0));
		Rock->Add(Vector(-10000, 10000,0));
		Rock->Add(Vertex(0,0,0));
		Rock->Add(Vertex(1,1,0));
		Rock->Add(Vertex(2,1,1));
		Rock->Add(Vertex(3,0,1));
		IndexedPolygon *pol = Rock->NewIndexedPolygon();
		pol->Add(0);
		pol->Add(1);
		pol->Add(2);
		pol->Add(3);
		Rocks_sub_sub->Add(Rock);
		bar->Tick();
	}
*/	delete bar;
/*
	printf("Shaping rocks..\n");
//	int rCount = 10*count;
//	ConsoleProgressBar
	bar = new ConsoleProgressBar(40,rCount+rCount*3+rCount*3*3);
	for(n=0; n<rCount; n++){
		Geometry *Rock = (Geometry*)Rocks->GetItem(n); //new Geometry();
		RockAI *AI_Rock = new RockAI(this,Rock,40000.0f);
		Rock->Node::Apply(AI_Rock);
		AI_Rocks->Add(AI_Rock);
		bar->Tick();
	}

	for(n=0; n<rCount*3; n++){
		Geometry *Rock = (Geometry*)Rocks_sub->GetItem(n); //new Geometry();
		RockAI *AI_Rock = new RockAI(this,Rock);
		Rock->Node::Apply(AI_Rock);
		AI_Rocks->Add(AI_Rock);
		bar->Tick();
	}
	for(n=0; n<rCount*3*3; n++){
		Geometry *Rock = (Geometry*)Rocks_sub_sub->GetItem(n); //new Geometry();
		RockAI *AI_Rock = new RockAI(this,Rock);
		Rock->Node::Apply(AI_Rock);
		AI_Rocks->Add(AI_Rock);
		bar->Tick();
	}
	delete bar;
*/
}

void Meteorites::NextLevel(int rCount){
	Rocks_sub_item = 0;
	Rocks_sub_sub_item = 0;
	RockCount = rCount+rCount*3+rCount*3*3;
	for(int n=0; n<rCount; n++) null->Node::Apply((Geometry*)Rocks->GetItem(n));
}
/*
void Meteorites::MessageLoop(void){
	quit = false;
	//int tr=0;
	while(!quit||!allowquit){
		Sleep(500);
		//Info3->SetTranslusency(float(tr++&0xff)/255.0f);
	}
	printf("Leaving message loop. %d,%d\n",quit,allowquit);
}
*/
#include <time.h>

void Meteorites::Refresh(WindowScreen *scr){
	int t=int(float(clock())*(1.0f/CLOCKS_PER_SEC)*256.0f);
	//printf("%d\n",tr);
	//tr&=0x3ff;
	//if(tr&0x3ff<=0xff) Info1->SetTranslusency(float(tr&0xff)/255.0f);
	//else Info1->SetTranslusency(1.0f);
	//if(tr&0x3ff>0xff&&tr&0x3ff<=0x1ff) Info2->SetTranslusency(float((tr>>1)&0xff)/255.0f);
	//else Info2->SetTranslusency(1.0f);

	t=t%0x800;

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
		else if(tr>=0x400) Info3->SetTranslusency(float(tr&0xff)/255.0f);
	}else Info3->SetTranslusency(1.0f);

	scr->Refresh();
}

struct RefreshArgs{
	WindowScreen	*scr;
	Meteorites		*game;
	bool			bailout;
};

void RefreshThread(RefreshArgs *args){
	while(!args->bailout) args->game->Refresh(args->scr);
	args->bailout = false;
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

void Meteorites::MessageReceived(void){
/*	int cnt = GetReceivedCount();
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
			printf("GAME_START\n");
			int32 s;
			Get(s);
			WindowScreen *scr = (WindowScreen*)s;
			scr->SetClearState(false);
			scr->Apply(View1);

			rfargs = new RefreshArgs;
			rfargs->scr = scr;
			rfargs->game = this;
			rfargs->bailout = false;

			DWORD dwThreadID;
			CreateThread(
				NULL,
				0,
				(LPTHREAD_START_ROUTINE)RefreshThread,
				rfargs,
				0,
				&dwThreadID);
		}break;
		case GAME_STOP:
			printf("GAME_STOP\n");
			rfargs->bailout = true;
			while(rfargs->bailout) Sleep(500);
			delete rfargs;
			allowquit=true;
		break;
		}
	}*/
}
/*
void main(int,char**){
	Meteorites *game = new Meteorites();
	game->MessageLoop();
	printf("Deleting game\n");
	delete game;
	printf("Leaving\n");
}
*/
void Meteorites::MessageLoop(void){
	WindowScreen *scr = new WindowScreen();
	scr->SetClearState(false);
	scr->Apply(View1);
	int n=1000;
	while(n-->0) scr->Refresh();
	delete scr;
}

void main(int,char**){
	Meteorites *game = new Meteorites();
//	game->MessageLoop();
//	printf("Deleting game\n");
	game->MessageLoop();
	delete game;
//	printf("Leaving\n");
}

#if 0
/**************************************************************\
|      Copyright (C) 1997 RealityMakers Entertainment AS       |
|                     All rights reserved.                     |
\**************************************************************/

#define rand foo
#include "Meteorites.h"
#include <Interface/DynamicArray.h>
#include <3dapi/Geometry.h>
#include <3dapi/IndexedPolygon.h>
#include "RockAI.h"
#include <Interface/View.h>
#include <Interface/Bitmap.h>
#include <3dapi/Texture.h>
#include <3dapi/Material.h>
#include "Background.h"
#include "Player.h"
#include <3dapi/Camera.h>
#include "CameraAI.h"
#include <3dapi/Network/Host.h>
#include <Interface/WindowScreen.h>
#include <Interface/Font.h>
//#include "GameServer.h"

#undef rand
#undef abs
#include <windows.h>
#include "GameDLL.h"

#include <Interface/Debug.h>

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

Meteorites::Meteorites() : Client(), Message(){

	SetName("MeteoritesGame");

	printf("------------------------------------------------------------------------\n");
	printf("Initializing TV-Meteorites, Copyright (C) RealityMakers Entertainment as\n");
	printf("------------------------------------------------------------------------\n");

//	char *str = new char[strlen(GetCurrentProcess()->GetName())+];
//	SetName();

	extern Host *host;
	AttatchHook  = host->CreateHook("Attatch");
	DetatchHook  = host->CreateHook("Detatch");
	ShutDownHook = host->CreateHook("ShutDown");

	View1 = new View(Rect(0,0,1,1));
	View1->SetClearState(false);

	ScoreViews = new DynamicArray();
	font = new Font("Fonts/Swiss");
	for(int n=0; n<16; n++){
		View *v = new View(Rect(.8f,float(n)*.6f/16.0f,1,float(n+1)*.6f/16.0f));
		v->ConsoleStream::Apply(font);
		v->SetClearState(false);
		v->Print("0");
		switch(n){
		case 0:  v->SetColor(ARGB(1,0,0)); break;
		case 1:  v->SetColor(ARGB(0,0,1)); break;
		case 2:  v->SetColor(ARGB(1,1,0)); break;
		case 3:  v->SetColor(ARGB(0,1,0)); break;
		case 4:  v->SetColor(ARGB(1,.5f,.5f)); break;
		case 5:  v->SetColor(ARGB(0,1,1)); break;
		case 6:  v->SetColor(ARGB(.5f,.5f,.5f)); break;
		case 7:  v->SetColor(ARGB(1,0,0)); break;
		case 8:  v->SetColor(ARGB(1,0,0)); break;
		case 9:  v->SetColor(ARGB(1,0,0)); break;
		case 10: v->SetColor(ARGB(1,0,0)); break;
		case 11: v->SetColor(ARGB(1,0,0)); break;
		case 12: v->SetColor(ARGB(1,0,0)); break;
		case 13: v->SetColor(ARGB(1,0,0)); break;
		case 14: v->SetColor(ARGB(1,0,0)); break;
		case 15: v->SetColor(ARGB(1,0,0)); break;
		}
		View1->Apply(v);
		ScoreViews->Add(v);
	}
/*
	ScoreView = new View(Rect(.8f,0,1,.5f));
	ScoreView->SetClearState(false);
	ScoreView->ConsoleStream::Clear();
	ScoreView->Print(" 1: 1261\n 2: 8726\n");
	ScoreView->Print(" 3: 8145\n 4: 6923\n");
	ScoreView->Print(" 5: 1261\n 6: 8726\n");
	ScoreView->Print(" 7: 8145\n 8: 6923\n");
	ScoreView->Print(" 9: 1261\n10: 8726\n");
	ScoreView->Print("11: 8145\n12: 6923\n");
	ScoreView->Print("13: 1261\n14: 8726\n");
	ScoreView->Print("15: 8145\n16: 6923\n");
	font = new Font("Fonts/Swiss");
	ScoreView->ConsoleStream::Apply(font);
	View1->Apply(ScoreView);
*/
//	View2 = new View(Rect(.8f,0,1,.5f));
	View4 = new View(Rect(.75f,0,1,.8f));
//	View2->SetClearState(false);
//	View4->SetClearState(false);

	MeteoritesBitmap = new Bitmap("Textures/test"/*Textures/Title/title"*/,BITMAP_RGB); //Titletv4");
	View *LoadView = new View(Rect(.2f,.2f,1-.2f,1-.2f));
	View4->Apply(MeteoritesBitmap);
View1->Apply(View4);
	// Initialize scene

	null = new Geometry();
	null->SetPosition(Vector(0,0,1000000));

	Back = new Geometry();
	Back->Node::Apply(new Background(Back));
	Back->SetPosition(Vector(0,0,1000000));
	Back->Post();
	null->Node::Apply(Back);

	cam = new Camera();
	cam->SetName("Camera");
	null->Node::Apply(cam);
	camAI = new CameraAI(cam);
	cam->Apply(camAI);

	View1->Attatch(cam);

	PlayerGeometries = new DynamicArray();
	for(n=0; n<5; n++){
		Geometry *Ship = new Geometry();
		char name[1024];
		sprintf(name,"Player%d",n);
		Ship->SetName(name);
		//Ship->SetPosition(Vector(0,0,-800000));
		Ship->Post();
		PlayerGeometries->Add(Ship);
		//AI_Player1 = new PlayerAI(Ship);
		null->Node::Apply(Ship);
		Ship->Node::Apply(new PlayerAI(Ship,(View*)ScoreViews->GetItem(n)));
	}

	//

	printf("Initializing levels.\n");
	//#ifndef _DEBUG
	InitLevels(2);
	NextLevel(10);
	//#endif
	printf("Done.\n");

	printf("------------------------------------------------------------------------\n");
	printf("                       TV-Meteorites initalized\n");
	printf("------------------------------------------------------------------------\n");

	Initialized = true;
}

Meteorites::~Meteorites(){
	delete View1;
	delete PlayerGeometries;
//	delete ScoreView;
	delete font;
	delete View4;
	delete MeteoritesBitmap;
/*
	delete View2;
*/
	null->Kill();
}

void Meteorites::InitLevels(int count){
	Rocks = new DynamicArray();
	Rocks_sub = new DynamicArray();
	Rocks_sub_sub = new DynamicArray();
	AI_Rocks = new DynamicArray();
	Rocks_sub_item = 0;
	Rocks_sub_sub_item = 0;
	RockCount = 0;

	printf("Creating rocks...\n");
	int rCount = 10*count;
	ConsoleProgressBar *bar = new ConsoleProgressBar(40,rCount+rCount*3+rCount*3*3);
	for(int n=0; n<rCount; n++){
		Geometry *Rock = new Geometry();
		Rock->SetName("Rock");
/*
		Rock->Add(Vector(-40000,-40000,0));
		Rock->Add(Vector( 40000,-40000,0));
		Rock->Add(Vector( 40000, 40000,0));
		Rock->Add(Vector(-40000, 40000,0));
		Rock->Add(Vertex(0,0,0));
		Rock->Add(Vertex(1,1,0));
		Rock->Add(Vertex(2,1,1));
		Rock->Add(Vertex(3,0,1));
		IndexedPolygon *pol = Rock->NewIndexedPolygon();
		pol->Add(0);
		pol->Add(1);
		pol->Add(2);
		pol->Add(3);
*/
		Rocks->Add(Rock);
		RockAI *AI_Rock = new RockAI(this,Rock,40000.0f);
		Rock->Node::Apply(AI_Rock);
//		AI_Rocks->Add(AI_Rock);
		bar->Tick();
	}
/*
	for(n=0; n<rCount*3; n++){
		Geometry *Rock = new Geometry();
		Rock->SetName("Rock_sub");
		Rock->Add(Vector(-20000,-20000,0));
		Rock->Add(Vector( 20000,-20000,0));
		Rock->Add(Vector( 20000, 20000,0));
		Rock->Add(Vector(-20000, 20000,0));
		Rock->Add(Vertex(0,0,0));
		Rock->Add(Vertex(1,1,0));
		Rock->Add(Vertex(2,1,1));
		Rock->Add(Vertex(3,0,1));
		IndexedPolygon *pol = Rock->NewIndexedPolygon();
		pol->Add(0);
		pol->Add(1);
		pol->Add(2);
		pol->Add(3);
		Rocks_sub->Add(Rock);
		bar->Tick();
	}
	for(n=0; n<rCount*3*3; n++){
		Geometry *Rock = new Geometry();
		Rock->SetName("Rock_sub_sub");
		Rock->Add(Vector(-10000,-10000,0));
		Rock->Add(Vector( 10000,-10000,0));
		Rock->Add(Vector( 10000, 10000,0));
		Rock->Add(Vector(-10000, 10000,0));
		Rock->Add(Vertex(0,0,0));
		Rock->Add(Vertex(1,1,0));
		Rock->Add(Vertex(2,1,1));
		Rock->Add(Vertex(3,0,1));
		IndexedPolygon *pol = Rock->NewIndexedPolygon();
		pol->Add(0);
		pol->Add(1);
		pol->Add(2);
		pol->Add(3);
		Rocks_sub_sub->Add(Rock);
		bar->Tick();
	}
*/	delete bar;
/*
	printf("Shaping rocks..\n");
//	int rCount = 10*count;
//	ConsoleProgressBar
	bar = new ConsoleProgressBar(40,rCount+rCount*3+rCount*3*3);
	for(n=0; n<rCount; n++){
		Geometry *Rock = (Geometry*)Rocks->GetItem(n); //new Geometry();
		RockAI *AI_Rock = new RockAI(this,Rock,40000.0f);
		Rock->Node::Apply(AI_Rock);
		AI_Rocks->Add(AI_Rock);
		bar->Tick();
	}

	for(n=0; n<rCount*3; n++){
		Geometry *Rock = (Geometry*)Rocks_sub->GetItem(n); //new Geometry();
		RockAI *AI_Rock = new RockAI(this,Rock);
		Rock->Node::Apply(AI_Rock);
		AI_Rocks->Add(AI_Rock);
		bar->Tick();
	}
	for(n=0; n<rCount*3*3; n++){
		Geometry *Rock = (Geometry*)Rocks_sub_sub->GetItem(n); //new Geometry();
		RockAI *AI_Rock = new RockAI(this,Rock);
		Rock->Node::Apply(AI_Rock);
		AI_Rocks->Add(AI_Rock);
		bar->Tick();
	}
	delete bar;
*/
}

void Meteorites::NextLevel(int rCount){
	Rocks_sub_item = 0;
	Rocks_sub_sub_item = 0;
	RockCount = rCount+rCount*3+rCount*3*3;
	for(int n=0; n<rCount; n++) null->Node::Apply((Geometry*)Rocks->GetItem(n));
}
/*
void Meteorites::MessageLoop(void){
	quit = false;
	while(!quit||!allowquit){
		Sleep(500);
	}
	printf("Leaving message loop. %d,%d\n",quit,allowquit);
}

struct RefreshArgs{
	WindowScreen	*scr;
	bool			bailout;
};

void RefreshThread(RefreshArgs *args){
	while(!args->bailout) args->scr->Refresh();
	args->bailout = false;
}
*/
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

void Meteorites::MessageReceived(void){
/*
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
			printf("GAME_START\n");
			int32 s;
			Get(s);
			WindowScreen *scr = (WindowScreen*)s;
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
		}break;
		case GAME_STOP:
			printf("GAME_STOP\n");
			rfargs->bailout = true;
			while(rfargs->bailout) Sleep(500);
			delete rfargs;
			allowquit=true;
		break;
		}
	}
*/
}

void Meteorites::MessageLoop(void){
	WindowScreen *scr = new WindowScreen();
	scr->SetClearState(false);
	scr->Apply(View1);
	int n=1000;
	while(n-->0) scr->Refresh();
	delete scr;
}

void main(int,char**){
	Meteorites *game = new Meteorites();
//	game->MessageLoop();
//	printf("Deleting game\n");
	game->MessageLoop();
	delete game;
//	printf("Leaving\n");
}

#endif
#endif
