
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/sys/types.h>
#include <posix/stdlib.h>
#include <posix/stdio.h>
#include <posix/time.h>
#include <posix/string.h>
#include <Interface/DynamicArray.h>
#include <Interface/Font.h>
#include <Interface/Bitmap.h>
#include <Interface/Rect.h>
#include <Interface/View.h>
#include <Interface/String.h>
#include "ScoreViews.h"
#include <assert.h>

struct Player{
	bool	active;
	int		num;
	char	name[4];
	int		score;
	View	*NameView;
	View	*numview;
	View	*View;
};

class Players : public DynamicArray{
public:		Players() : DynamicArray(){}
	bool	Swap(void *_a, void *_b){
				Player *a = (Player*)_a;
				Player *b = (Player*)_b;
				return(a->score<b->score);
			}
};

ScoreViews::ScoreViews(View *parent){// : Semaphore(){
//	Acquire();

	msg = new Message();

	Views = new DynamicArray();
	BitmapBunch = new DynamicArray();
	ViewBunch = new DynamicArray();
	//font = new Font("Fonts/arial15pt1");
	font = new Font("Fonts/swed");//Humnst777_BT_40"); //swiss");   //arial15pt1");
	font->SetSize(.035f);
	players = new Players();
	for(int n=0; n<MAX_PLAYERS; n++){		// 12.5 x 23.3, 54.2 x 23.3

		connect_log[n] = -1;

		#define xofs	.02f
		#define yofs	.1f
		#define width  (.233f*.65f)
		#define height (((.125f+.542f)/16.0f)*.65f)
		#define spacing ((0.1666667f/100.0f)*3.0f)

		char str[1024];
		sprintf(str,"Textures/interface/playernum/no%d",n+1);
		Bitmap *PlayerNBitmap = new Bitmap(str,Bitmap::cRGB); //Titletv4");
		#ifdef _DEBUG
		BitmapBunch->Add(PlayerNBitmap,__FILE__,__LINE__);
		#else
		BitmapBunch->Add(PlayerNBitmap);
		#endif
		View *PlayerNView = new View(Rect(1+1-width-height+xofs,1+float(n)*height+yofs,1+1-width-spacing+xofs,1+float(n)*height+height-spacing+yofs));
		#ifdef _DEBUG
		ViewBunch->Add(PlayerNView,__FILE__,__LINE__);
		#else
		ViewBunch->Add(PlayerNView);
		#endif
		PlayerNView->Apply(PlayerNBitmap);
		PlayerNView->SetClearState(false);
		parent->Apply(PlayerNView);

		float scl = 1-width-height*2.0f+xofs;
		float sct = float(n)*height+yofs-.005f;
		float scr = 1-width-height+xofs;
		float scb = sct+height;
//		float xs = (scr-scl)*.2f;
//		float ys = (scb-sct)*.2f;
//		scl+=xs;
//		scr-=xs;
//		sct+=ys;
//		scb-=ys;
/*		switch(n){
		Bitmap *PlaceBitmap;
		View *PlaceView;
		case 0:
			BitmapBunch->Add(PlaceBitmap = new Bitmap("Textures/interface/first",BITMAP_RGB)); //Titletv4");
			ViewBunch->Add(PlaceView = new View(Rect(scl,sct,scr,scb)));
			PlaceView->Apply(PlaceBitmap);
			PlaceView->SetClearState(false);
			parent->Apply(PlaceView);
		break;
		case 1:
			BitmapBunch->Add(PlaceBitmap = new Bitmap("Textures/interface/second",BITMAP_RGB)); //Titletv4");
			ViewBunch->Add(PlaceView = new View(Rect(scl,sct,scr,scb)));
			PlaceView->Apply(PlaceBitmap);
			PlaceView->SetClearState(false);
			parent->Apply(PlaceView);
		break;
		case 2:
			BitmapBunch->Add(PlaceBitmap = new Bitmap("Textures/interface/third",BITMAP_RGB)); //Titletv4");
			ViewBunch->Add(PlaceView = new View(Rect(scl,sct,scr,scb)));
			PlaceView->Apply(PlaceBitmap);
			PlaceView->SetClearState(false);
			parent->Apply(PlaceView);
		break;
		}
*/
		#define fontscale  0
		#define yo (-.0105f)
		View *v = new View(Rect(1+1-width+xofs,1+float(n)*height+fontscale+yofs+yo,1+xofs,1+float(n)*height+height-spacing-fontscale+yofs));
		v->/*ConsoleStream::*/Apply(font);
		v->SetClearState(false);
		#ifdef _DEBUG
		ViewBunch->Add(v,__FILE__,__LINE__);
		#else
		ViewBunch->Add(v);
		#endif
		v->Print("     0");
		v->SetColor(ARGB(.7f,.7f,.7f));
		parent->Apply(v);
		#ifdef _DEBUG
		Views->Add(v,__FILE__,__LINE__);
		#else
		Views->Add(v);
		#endif

		View *nv = new View(Rect(1+1-width+xofs,1+float(n)*height+fontscale+yofs+yo,1+xofs,1+float(n)*height+height-spacing-fontscale+yofs));
		nv->/*ConsoleStream::*/Apply(font);
		nv->SetClearState(false);
		#ifdef _DEBUG
		ViewBunch->Add(nv,__FILE__,__LINE__);
		#else
		ViewBunch->Add(nv);
		#endif
		nv->Print("a");
		nv->SetColor(ARGB(.7f,.7f,.7f));
		parent->Apply(nv);
		#ifdef _DEBUG
		Views->Add(nv,__FILE__,__LINE__);
		#else
		Views->Add(nv);
		#endif

		Player *pl = new Player;
		pl->num   = n;
		pl->name[0] = '\0';
		pl->score = 0;
		pl->View = v;
		pl->NameView = nv;
		pl->numview = PlayerNView;
		pl->active = false;
		#ifdef _DEBUG
		players->Add(pl,__FILE__,__LINE__);
		#else
		players->Add(pl);
		#endif
	}

	for(n=0; n<10; n++){
		hiscore.score[n]=0;
		sprintf(hiscore.name[n],"ano");
	}
//	Release();
}

ScoreViews::~ScoreViews(){
//	Acquire();
	while(ViewBunch->GetCount()){
		delete (View*)ViewBunch->GetItem(0);
		#ifdef _DEBUG
		ViewBunch->Remove(0,__FILE__,__LINE__);
		#else
		ViewBunch->Remove(0);
		#endif
	}
	delete ViewBunch;
	while(BitmapBunch->GetCount()){
		delete (Bitmap*)BitmapBunch->GetItem(0);
		#ifdef _DEBUG
		BitmapBunch->Remove(0,__FILE__,__LINE__);
		#else
		BitmapBunch->Remove(0);
		#endif
	}
	delete BitmapBunch;
	delete Views;
	delete font;
	while(players->GetCount()){
		delete (Player*)players->GetItem(0);
		#ifdef _DEBUG
		players->Remove(0,__FILE__,__LINE__);
		#else
		players->Remove(0);
		#endif
	}
	delete players;
	delete msg;
//	Release();
}

void *ScoreViews::GetPlayer(int num){
//	Acquire();
	for(int n=0; n<MAX_PLAYERS; n++){
		Player *pl = (Player*)players->GetItem(n);
		if(pl->num==num){
//			Release();
			return pl;
		}
	}
assert(false);
//	Release();
	return 0;
}

char *ScoreViews::GetName(void *player){
//	Acquire();
	for(int n=0; n<MAX_PLAYERS; n++){
		void *pl = players->GetItem(n);
		if(pl==player){
//			Release();
			return ((Player*)pl)->name;
		}
	}
//	Release();
	return 0;
}

void ScoreViews::SetScore(void *_pl, int val){
//	Acquire();
	Player *pl = (Player*)_pl;
	pl->score = val;
	//Update();
	//char str[1024];
	//sprintf(str,"%d %s",val,pl->name);
	//pl->View->ConsoleStream::Clear();
	//pl->View->Print(str);
	Update();
//	Release();
}

void ScoreViews::Update(void){
//	Acquire();
	players->Sort();
	int item = 0;
	int packets = 0;
	for(int n=0; n<MAX_PLAYERS; n++){		// 12.5 x 23.3, 54.2 x 23.3

		#define xofs	.02f
		#define yofs	.1f
		#define width  (.233f*.65f)
		#define height (((.125f+.542f)/16.0f)*.65f)
		#define spacing ((0.1666667f/100.0f)*3.0f)
		#define texofs 0.0045f

		Player *pl = (Player*)players->GetItem(n);
		if(pl->active){
//printf("%d: %d\n",pl->num,pl->score);
			if(connect_log[pl->num]<0) connect_log[pl->num] = clock();
			pl->numview->Set(Rect(1-width-height+xofs,float(item)*height+yofs,1-width-spacing+xofs,float(item)*height+height-spacing+yofs));
			pl->View->Set(Rect(1-width+xofs,float(item)*height+fontscale+yofs+yo+texofs,1+xofs,float(item)*height+height-spacing-fontscale+yofs+texofs));
			pl->NameView->Set(Rect(1-width+xofs,float(item)*height+fontscale+yofs+yo+texofs,1+xofs,float(item)*height+height-spacing-fontscale+yofs+texofs));
			item++;
			char str[1024];
			//sprintf(str,"%d %s",pl->score,pl->name);
			sprintf(str,"     %d",pl->score);
			pl->View->ConsoleStream::Clear();
			pl->View->Print(str);
			sprintf(str,"%s",pl->name);
			pl->NameView->ConsoleStream::Clear();
			pl->NameView->Print(str);
		}else{
			if(connect_log[pl->num]>0){
//				printf("Player %d was connected %d clock ticks!\n",pl->num,clock()-connect_log[pl->num]);
				float time = float(clock()-connect_log[pl->num])/1000.0f;;
				//Message *msg = new Message();
//printf("%f,%s,%d\n",time,pl->name,pl->score);
#ifndef _DEBUG
				msg->AddPacket(0);		// fixme: 5/5-1998 (after 9 hours) Message::Packets:Array realocated after it was freed!
				msg->Add(time);
				msg->Add((signed char*)pl->name,strlen(pl->name));
				msg->Add((int32)pl->score);
#endif
				packets++;
				//msg->SendTo("LogCollector");	// this is related to the above fixme!
				//delete msg;
				connect_log[pl->num]=-1;
			}
pl->score = 0;
			pl->numview->Set(Rect(1+1-width-height+xofs,1+float(item)*height+yofs,1+1-width-spacing+xofs,1+float(item)*height+height-spacing+yofs));
			pl->View->Set(Rect(1+1-width+xofs,1+float(item)*height+fontscale+yofs+yo,1+1+xofs,1+float(item)*height+height-spacing-fontscale+yofs));
			pl->NameView->Set(Rect(1+1-width+xofs,1+float(item)*height+fontscale+yofs+yo,1+1+xofs,1+float(item)*height+height-spacing-fontscale+yofs));
		}
	}
#ifndef _DEBUG
	if(packets) msg->SendTo("LogCollector");	// this is related to the above fixme!
#endif
//	Release();
}

void ScoreViews::Activate(void *_pl){
//	Acquire();
	Player *pl = (Player*)_pl;
	pl->active = true;
//	Release();
}

void ScoreViews::Deactivate(void *_pl){
//	Acquire();
	Player *pl = (Player*)_pl;
	pl->active = false;
	// Update hiscore
	for(int n=0; n<10; n++){
		if(pl->score>hiscore.score[n]){
			for(int i=n; i<10-1; i++){
				hiscore.score[i+1]=hiscore.score[i];
				sprintf(hiscore.name[i+1],"%s",hiscore.name[i]);
			}
			hiscore.score[n] = pl->score;
			sprintf(hiscore.name[n],"%s",pl->name);
			break;
		}
	}
//	for(n=0; n<10; n++) printf("%d:\t%d\t%s\n",n+1,hiscore.score[n],hiscore.name[n]);
//	Release();
}

bool ScoreViews::IsActive(void *_pl){
	Player *pl = (Player*)_pl;
	return pl->active;
}
