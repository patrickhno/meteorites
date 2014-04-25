
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include <string.h>
#include "Fireball.h"
#include <3dapi/Geometry.h>
#include <3dapi/IndexedPolygon.h>
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/Vertex.h>
#include "Player.h"
#include <Interface/String.h>

/*
class Explotion{
public:		Explotion();
			~Explotion();
};
*/

static Material *shot = 0;
//static Material *expm = 0;
static String name = String("Fireball");

Fireball::Fireball(Geometry *g, PlayerAI *m) : Intelligence(g){
	mother = m;

	g->SetName(0,name); //String("Fireball"));		// fixme: Optimize!

	SetPosition(Vector(m->GetPosition()));
	SetOrientation(Quaternion(m->GetOrientation()));

	if(!shot){
		shot = new Material("Textures/shot",Texture::cARGB);
		shot->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	}
//	if(!expm){
		expm = new Material("Textures/Explosion/Explosion",Texture::cARGB);
		expm->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
//		expm->CacheAll();
//	}
	g->Apply(shot);

	g->Add(Vector(-10*3,-30*3,0));
	g->Add(Vector( 10*3,-30*3,0));
	g->Add(Vector( 10*3, 30*3,0));
	g->Add(Vector(-10*3, 30*3,0));
	g->Add(Vertex(0,0,0));
	g->Add(Vertex(1,1,0));
	g->Add(Vertex(2,1,1));
	g->Add(Vertex(3,0,1));
	IndexedPolygon *pol;
	pol = g->NewIndexedPolygon();
	pol->Add(0);
	pol->Add(1);
	pol->Add(2);
	pol->Add(3);
	pol = g->NewIndexedPolygon();
	pol->Add(3);
	pol->Add(2);
	pol->Add(1);
	pol->Add(0);
//	g->SetPosition(Vector(GetParent()->GetPosition()));
//	g->SetName("Fireball");


	SpawnTime = -1.0f;

	Explode = false;

//	KillNodes = new DynamicArray();
	Speed = -150.0f;
}

Fireball::~Fireball(){
//	printf("Deleted %s\n",GetName());
}

bool Fireball::Tick(double time){
	SetPosition(Vector(GetPosition())+Vector(0,Speed,0)*Quaternion(GetOrientation()));
	if(SpawnTime<0){
//		printf("f: %s,%f,%f,%f\n",GetParent()->GetName(),GetPosition()->X,GetPosition()->Y,GetPosition()->Z);
		if(Explode) SpawnTime = time-2.8f;
		else SpawnTime = time;
	}
	if((time-SpawnTime)>3.0f){
		Kill();
		return false;
		//DisconnectOwner();
		//return false;
	}
	if(Explode){
		int framecount = expm->GetTexture()->GetFrameCount();
	//printf("Frame = %d/%d\n",int((time-SpawnTime-1.5f)*framecount/.5f)%framecount,framecount);
		if(framecount) expm->GetTexture()->SetFrame(int((time-SpawnTime-2.8f)*framecount/.2f)%framecount);
	}
	return true;
}

String nullname = String("null");
String Rockname = String("Rock");

bool Fireball::BoundingSphereIntersection(float sqrdist, class Node *caller){
	if(!Explode){
		if(caller!=mother->GetCreatorGeometry()->GetNode()){
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
			else*/ if(caller->GetName()==Rockname){ //String(String("Rock"))){			// fixme: Optimize!
				mother->AddScore(100);
				Explode = true;
				GetCreatorGeometry()->Apply(expm);
				GetCreatorGeometry()->SetName(0,nullname); //"null");
				GetCreatorGeometry()->SetVector(0,Vector(-50*3,-50*3,0));
				GetCreatorGeometry()->SetVector(1,Vector( 50*3,-50*3,0));
				GetCreatorGeometry()->SetVector(2,Vector( 50*3, 50*3,0));
				GetCreatorGeometry()->SetVector(3,Vector(-50*3, 50*3,0));
				SpawnTime = -1.0f;
				Speed/=2.0f;
			}
		}
	}
	return false;
}

