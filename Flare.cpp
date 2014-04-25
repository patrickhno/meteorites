
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include <posix/stdio.h>

#include <string.h>
#include "Flare.h"
#include <3dapi/Geometry.h>
#include <3dapi/IndexedPolygon.h>
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/Vertex.h>
#include "Player.h"
#include "Sparcle.h"
#include <Interface/String.h>
#include "ScoreViews.h"

/*
class Explotion{
public:		Explotion();
			~Explotion();
};
*/

//#include <posix/stdio.h>

//template <class T> class Leftover : public T{
//public:	Leftover(){ printf("hey!\n"); };
//};
/*
template<class T> class Leftover{
public:	Leftover(T j){ junk = j; }
		~Leftover(){ delete junk; }
private:
	T	*junk;
};
*/

#include <Interface/Garbage.h>

static Material *shot = 0; // = new Material("Textures/shot",TEXTURE_ARGB);
static Material *expm = 0;
#ifdef BUG_TEST
static Message *message = 0;
#endif
//static int count = 0;

static void GarbageCollector(void){
	if(shot) delete shot;
	if(expm) delete expm;
	#ifdef BUG_TEST
	if(message) delete message;
	#endif
}

Flare::Flare(Geometry *g, PlayerAI *m, void *_player, ScoreViews *_Scores) : Intelligence(g){
//	count++;
//	printf("%d\n",count);
	mother = m;
mother_name = m->GetName();
//	sprintf(mother_name,"%s",m->GetName().GetString());
	player = _player;
	Scores = _Scores;
	g->SetName(0,String("Flare"));		// fixme: Optimize!

	SetPosition(Vector(m->GetPosition())+Vector(0,-500,0)*Quaternion(m->GetOrientation()));
	SetOrientation(Quaternion(m->GetOrientation()));

	if(!shot){
		shot = new Material("Textures/shot",Texture::cARGB);
		shot->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
		//Leftover(shot);
		AddGarbageCollector(GarbageCollector);
	}
	if(!expm){
		expm = new Material("Textures/Explosion/Explosion",Texture::cARGB);
		expm->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
//		expm->CacheAll();
		//Leftover(expm);
	}
	#ifdef BUG_TEST
	if(!message) message = new Message();
	#endif
	g->Apply(shot);

	g->Add(Vector(-10*3,-30*3,0));
	g->Add(Vector( 10*3,-30*3,0));
	g->Add(Vector( 10*3, 30*3,0));
	g->Add(Vector(-10*3, 30*3,0));
	g->Add(Vertex(0,0,0));
	g->Add(Vertex(1,1,0));
	g->Add(Vertex(2,1,1));
	g->Add(Vertex(3,0,1));
//	IndexedPolygon *pol;
//	pol = g->NewIndexedPolygon();
//	pol->Add(0);
//	pol->Add(1);
//	pol->Add(2);
//	pol->Add(3);
	pol = g->NewIndexedPolygon();
	pol->Add(3);
	pol->Add(2);
	pol->Add(1);
	pol->Add(0);
//	g->SetPosition(Vector(GetParent()->GetPosition()));
//	g->SetName("Flare");


	SpawnTime = -1.0f;

	Explode = false;

//	KillNodes = new DynamicArray();
	Speed = -3000.0f;
	Velocity = Vector(0,Speed,0)*Quaternion(GetOrientation());
}

Flare::~Flare(){
//	count--;
//	printf("Deleted %s\n",GetName());
}

bool Flare::Tick(double time){
	if(SpawnTime<0){
//		printf("f: %s,%f,%f,%f\n",GetParent()->GetName(),GetPosition()->X,GetPosition()->Y,GetPosition()->Z);
		if(Explode) oldtime = time, spawnsparcle = SpawnTime = time-2.5f;
		else oldtime = spawnsparcle = SpawnTime = time;
//new Sparcle();
	}
	SetPosition(Vector(GetPosition())+Velocity*float(time-oldtime));
	oldtime = time;
//printf("%s\n",GetName());
	if((time-SpawnTime)>3.0f){
		Kill();
		return false;
		//DisconnectOwner();
		//return false;
	}

	if(Explode){
		int framecount = expm->GetTexture()->GetFrameCount();
		if(framecount) expm->GetTexture()->SetFrame(int((time-SpawnTime-2.5f)*framecount*.5f)%framecount);
	}
//	else{
//		while(time-spawnsparcle>0){
//			spawnsparcle+=.2f;
//			new Sparcle(this);
//		}
//	}

	return true;
}

static String Player1Name	= String("Player0");
static String Player2Name	= String("Player1");
static String Player3Name	= String("Player2");
static String Player4Name	= String("Player3");
static String Player5Name	= String("Player4");
static String Player6Name	= String("Player5");
static String Player7Name	= String("Player6");
static String Player8Name	= String("Player7");
static String Player9Name	= String("Player8");
static String Player10Name	= String("Player9");
static String Player11Name	= String("Player10");
static String Player12Name	= String("Player11");
static String Player13Name	= String("Player12");
static String Player14Name	= String("Player13");
static String Player15Name	= String("Player14");
static String Player16Name	= String("Player15");
static String Player17Name	= String("Player16");
static String Player18Name	= String("Player17");
static String Player19Name	= String("Player18");
static String Player20Name	= String("Player19");
static String Player21Name	= String("Player20");
static String Player22Name	= String("Player21");
static String Player23Name	= String("Player22");
static String Player24Name	= String("Player23");
static String Player25Name	= String("Player24");
static String Player26Name	= String("Player25");
static String Player27Name	= String("Player26");
static String Player28Name	= String("Player27");
static String Player29Name	= String("Player28");
static String Player30Name	= String("Player29");

bool Flare::BoundingSphereIntersection(float sqrdist, class Node *caller){
	if(!Explode){
//		if(caller!=mother->GetCreatorGeometry()->GetNode()){	// fixme: Crashed here 25/4-1998 (mother was fucked)
		if(caller->GetName()!=mother_name){
/*
				 if(!strcmp(caller->GetName(),"Player1")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player2")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player3")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player4")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player5")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player6")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player7")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player8")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player9")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player10")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player11")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player12")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player13")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player14")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player15")) caller->Kill();
			else if(!strcmp(caller->GetName(),"Player16")) caller->Kill();
			else*/

			if(	caller->GetName()==Player1Name|| //String("Player1")||		// fixme: Optimize!
				caller->GetName()==Player2Name||
				caller->GetName()==Player3Name||
				caller->GetName()==Player4Name||
				caller->GetName()==Player5Name||
				caller->GetName()==Player6Name||
				caller->GetName()==Player7Name||
				caller->GetName()==Player8Name||
				caller->GetName()==Player9Name||
				caller->GetName()==Player10Name||
				caller->GetName()==Player11Name||
				caller->GetName()==Player12Name||
				caller->GetName()==Player13Name||
				caller->GetName()==Player14Name||
				caller->GetName()==Player15Name||
				caller->GetName()==Player16Name||
				caller->GetName()==Player17Name||
				caller->GetName()==Player18Name||
				caller->GetName()==Player19Name||
				caller->GetName()==Player20Name||
				caller->GetName()==Player21Name||
				caller->GetName()==Player22Name||
				caller->GetName()==Player23Name||
				caller->GetName()==Player24Name||
				caller->GetName()==Player25Name||
				caller->GetName()==Player26Name||
				caller->GetName()==Player27Name||
				caller->GetName()==Player28Name||
				caller->GetName()==Player29Name||
				caller->GetName()==Player30Name){
//printf("%s,%s\n",mother_name.GetString(),caller->GetName().GetString());
				PlayerAI *pl = (PlayerAI*)caller->GetIntelligence();
				if(pl->IsAlive()){

					#ifndef BUG_TEST
					mother->AddScore(100);	// fixme: Crash bug! (Probably when player are loging out)
					#else
					message->AddPacket(PlayerAI::ADD_SCORE);
					message->Add(int32(100));
					message->SendTo((char*)mother_name.GetString());
					#endif

					Explode = true;
					pol->Apply(expm);
					GetCreatorGeometry()->SetName(0,"null");
					GetCreatorGeometry()->SetVector(0,Vector(-50*3,-50*3,0));
					GetCreatorGeometry()->SetVector(1,Vector( 50*3,-50*3,0));
					GetCreatorGeometry()->SetVector(2,Vector( 50*3, 50*3,0));
					GetCreatorGeometry()->SetVector(3,Vector(-50*3, 50*3,0));
					SpawnTime = -1.0f;
					Speed/=2.0f;

					pl->Explode();
				}
			}else if(caller->GetName()==String("Rock")){	// fixme: Optimize!
				if(Scores) if(Scores->IsActive(player)){
					#ifndef BUG_TEST
					 mother->AddScore(100);	// fixme: Crash when player is removed.
					#else
					message->AddPacket(PlayerAI::ADD_SCORE);
					message->Add(int32(100));
					message->SendTo((char*)mother_name.GetString());
					#endif
				}
				Explode = true;
				pol->Apply(expm);
				GetCreatorGeometry()->SetName(0,"null");
				GetCreatorGeometry()->SetVector(0,Vector(-50*3,-50*3,0));
				GetCreatorGeometry()->SetVector(1,Vector( 50*3,-50*3,0));
				GetCreatorGeometry()->SetVector(2,Vector( 50*3, 50*3,0));
				GetCreatorGeometry()->SetVector(3,Vector(-50*3, 50*3,0));
				SpawnTime = -1.0f;
				Speed/=2.0f;
			}//else printf("%s\n",caller->GetName().GetString());
		}
	}
	return false;
}

Vector *Flare::GetVelocity(void){
	return &Velocity;
}
