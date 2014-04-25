
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
//#include <Interface/Debug.h>

#include <3dapi/Geometry.h>
#include "RockAI.h"
#include <3dapi/Texture.h>
#include <3dapi/Material.h>
#include "Meteorites.h"
#include <Interface/DynamicArray.h>
#include <3dapi/Camera.h>
#include <3dapi/LightPoint.h>
#include "FirePickup.h"
#include <posix/stdio.h>
#include <posix/string.h>
#include <3dapi/IndexedPolygon.h>
#include <3dapi/Vertex.h>
#include <Interface/String.h>

//static Material *mats[] = {0,0,0,0,0};
static int deadrocks = 0;
//static Material *expm = 0;

RockAI::RockAI(Camera *cam, /*Meteorites *_scr,*/ Geometry *c, float s) : Intelligence(c){ // ,KernelClient(){
	camera = cam;
//	scr=_scr;
	size = s;
	PositionStep=Vector(0,0,0);
//	Kill=false;
	startframe = abs(rand());
//	OldTime=Time();
	OldTime = -1.0f;

	c->SetName(0,String("Rock"));		// fixme: Optimize!

	SetPosition(Vector((rand()-0x40000)*.08f,(rand()-0x40000)*.08f,-8000));
	PositionStep=Vector(((rand()%0x7ff)-0x400)*1.0f,((rand()%0x7ff)-0x400)*1.0f,0);
	int rockmat = rand()%4;
	//if(!mats[rockmat]){
		char name[1024];
		sprintf(name,"Textures/Rock_%d/Rock_%d",rockmat,rockmat);
		RockMaterial = new Material(name,Texture::cRGB);
//		RockMaterial->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
		RockMaterial->CacheAll();
	//	mats[rockmat] = RockMaterial;
	//}
	//if(!expm){
	ExplotionMaterial[0] = new Material("Textures/Explosion/Explosion_0",Texture::cRGB);
//	ExplotionMaterial[0]->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	ExplotionMaterial[0]->CacheAll();
	ExplotionMaterial[1] = new Material("Textures/Explosion/Explosion_1",Texture::cRGB);
//	ExplotionMaterial[1]->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	ExplotionMaterial[1]->CacheAll();
	ExplotionMaterial[2] = new Material("Textures/Explosion/Explosion_2",Texture::cRGB);
//	ExplotionMaterial[2]->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	ExplotionMaterial[2]->CacheAll();
	ExplotionMaterial[3] = new Material("Textures/Explosion/Explosion_3",Texture::cRGB);
//	ExplotionMaterial[3]->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	ExplotionMaterial[3]->CacheAll();
	//RockMaterial = mats[rockmat];
	c->Apply(RockMaterial);
	ExpTime=0;
	status = 0;

	c->Add(Vector(-size,-size,0));
	c->Add(Vector( size,-size,0));
	c->Add(Vector( size, size,0));
	c->Add(Vector(-size, size,0));
	c->Add(Vertex(0,0,0));
	c->Add(Vertex(1,1,0));
	c->Add(Vertex(2,1,1));
	c->Add(Vertex(3,0,1));
	IndexedPolygon *pol = c->NewIndexedPolygon();
	pol->Add(0);
	pol->Add(1);
	pol->Add(2);
	pol->Add(3);
	exploding = false;
	ImpactTime = -1.0f;
}
RockAI::RockAI(/*Meteorites *_scr,*/ Geometry *g, RockAI *) : Intelligence(g){ //,KernelClient(){
//	scr = _scr;
	PositionStep=Vector(0,0,0);
//	Kill=false;
	startframe = abs(rand());
//	OldTime=Time();
	OldTime = -1.0f;
	//SetPosition(Vector((rand()-0x4000)*8,(rand()-0x4000)*8,-800000));
	PositionStep=Vector((rand()-0x4000)*.05f,(rand()-0x4000)*.05f,0);
//	RockMaterial = new Material("Textures/Rock/Rock",TEXTURE_ARGB);
//	ExplotionMaterial = new Material("Textures/Explosion/Explosion");
//	g->Apply(RockMaterial);
	ExpTime=0;
	status = 0;
	exploding = false;
	ImpactTime = -1.0f;
}
RockAI::~RockAI(){
	delete RockMaterial;
	delete ExplotionMaterial[0];
	delete ExplotionMaterial[1];
	delete ExplotionMaterial[2];
	delete ExplotionMaterial[3];
}

Intelligence *RockAI::Clone(Geometry *g){
	return(new RockAI(/*scr,*/g,this));
}

bool RockAI::Tick(double time){
	if(OldTime<0) OldTime = time;
	float pulse=float(time-OldTime);
	SetPosition(Vector(GetPosition())+(PositionStep*pulse));
	Vector pos = Vector(GetPosition());
	//Node *n = GetNode("Camera");
	pos-=Vector(camera->GetPosition());	// fixme: bug! geo is 0 sometimes
	if(pos.X> 6400*2) SetPosition(Vector(GetPosition())-Vector(6400*2*2,0,0));
	if(pos.X<-6400*2) SetPosition(Vector(GetPosition())+Vector(6400*2*2,0,0));
	if(pos.Y> 6400*2) SetPosition(Vector(GetPosition())-Vector(0,6400*2*2,0));
	if(pos.Y<-6400*2) SetPosition(Vector(GetPosition())+Vector(0,6400*2*2,0));

#if 0
	if(Kill){
		if(ExpTime==0){
			ExpTime = time;

			if(!strcmp(GetCreatorGeometry()->GetName(),"Rock_sub")){
				status = 1;
				for(int n=0; n<3; n++){
					/*
					Geometry *Rock = (Geometry*)scr->Rocks_sub_sub->GetItem(scr->Rocks_sub_sub_item++);
					Rock->Tick(time);
						 if(GetParentCamera())		GetParentCamera()->Apply(Rock);		// Fireball removes it self
					else if(GetParentGeometry())	GetParentGeometry()->Node::Apply(Rock);	// Fireball removes it self
					else if(GetParentLightPoint())	GetParentLightPoint()->Apply(Rock);	// Fireball removes it self
					Rock->SetPosition(Vector(GetPosition()));
					*/
					Geometry *Rock = new Geometry();
					Rock->Node::Apply(new RockAI(scr,Rock));
					GetParent()->Apply(Rock);
				}
			}else if(!strcmp(GetCreatorGeometry()->GetName(),"Rock")){
				status = 0;
				for(int n=0; n<3; n++){
					/*
					Geometry *Rock = (Geometry*)scr->Rocks_sub->GetItem(scr->Rocks_sub_item++);
					Rock->Tick(time);
						 if(GetParentCamera())		GetParentCamera()->Apply(Rock);		// Fireball removes it self
					else if(GetParentGeometry())	GetParentGeometry()->Node::Apply(Rock);	// Fireball removes it self
					else if(GetParentLightPoint())	GetParentLightPoint()->Apply(Rock);	// Fireball removes it self
					Rock->SetPosition(Vector(GetPosition()));
					*/
					Geometry *Rock = new Geometry();
					Rock->Node::Apply(new RockAI(scr,Rock));
					GetParent()->Apply(Rock);
				}
			}else status=2;

			GetCreatorGeometry()->SetName("Explotion");
//			GetCreatorGeometry()->Apply(ExplotionMaterial);
			//GetCreatorGeometry()->SetPosition(Vector(GetPosition())-Vector(0,0,10000));
			if(rand()<0x2ff){
				// Add pickup
				Geometry *Pickup = new Geometry();
				FirePickup *AI = new FirePickup(Pickup);
				Pickup->Node::Apply(AI);
				Pickup->SetPosition(Vector(GetPosition()));
				GetParentGeometry()->Node::Apply(Pickup);
			}
		}
		int framecount = GetCreatorGeometry()->GetMaterial()->GetTexture()->GetFrameCount();
		if(framecount) GetCreatorGeometry()->GetMaterial()->GetTexture()->SetFrame((int)((time-ExpTime)*framecount/0.5f)%framecount);
		OldTime=time;
		if((time-ExpTime)>0.5f){
			scr->RockCount--;
			//KillOwner();
			switch(status){
			case 0:
				GetCreatorGeometry()->SetName("Rock");
			break;
			case 1:
				GetCreatorGeometry()->SetName("Rock_sub");
			break;
			case 2:
				GetCreatorGeometry()->SetName("Rock_sub_sub");
			break;
			}
			GetCreatorGeometry()->Apply(RockMaterial);
			Disconnect();
			return false;
		}else return true;
	}else{
		int framecount = /*GetCreatorGeometry()->GetMaterial()*/RockMaterial->GetTexture()->GetFrameCount();
		if(framecount) /*GetCreatorGeometry()->GetMaterial()->*/RockMaterial->GetTexture()->SetFrame(((int)(time*framecount/2.0f)+startframe)%framecount);
		OldTime=time;
		return true;
	}
#endif
	if(exploding){
//printf("%f\n",ImpactTime);
		if(ImpactTime<0) ImpactTime = time;
		int framecount = ExplotionMaterial[explotion]->GetTexture()->GetFrameCount();
		int frame = int((time-ImpactTime)*framecount);///.5f);
//printf("%d/%d(%f)\n",frame,framecount,time-ImpactTime);
		if(frame>=framecount) Kill();
		if(framecount) ExplotionMaterial[explotion]->GetTexture()->SetFrame(frame>=framecount?framecount-1:frame);
		OldTime=time;
	}else{
// fixme: 16/11/1998 - GetTexture() returned bullshit.
		int framecount = RockMaterial->GetTexture()->GetFrameCount();
		if(framecount) RockMaterial->GetTexture()->SetFrame(int((time*framecount/2.0f)+startframe)%framecount);
		OldTime=time;
	}
	return true;
}

bool RockAI::BoundingSphereIntersection(float sqrdist, class Node *caller){

// fixme: caller was fucked here once.

	if(exploding) return false;

	//char *name = caller->GetName();

	if( caller->GetName()==String("Fireball")||	// fixme: Optimize!
		caller->GetName()==String("Flare")){	// fixme: Optimize!
		//Kill=true;
//printf("%s\n",caller->GetName());

		if(rand()%0xff<10){
			Geometry *Pickup = new Geometry();
			Pickup->Node::Apply(0,new FirePickup(camera,Pickup));
			Pickup->SetPosition(0,Vector(GetPosition()));
			GetParent()->Apply(0,Pickup);
		}

		if(size>100.0f){
			for(int n=0; n<2; n++){
				Geometry *Rock = new Geometry();
				Rock->Node::Apply(0,new RockAI(camera,/*scr,*/Rock,size/2));
				Rock->SetPosition(0,Vector(GetPosition()));
				GetParent()->Apply(0,Rock);
			}
		}else{
			deadrocks++;
			while(deadrocks>=4){
				deadrocks-=4;
				Geometry *Rock = new Geometry();
				Rock->Node::Apply(0,new RockAI(camera,/*scr,*/Rock,400.0f));
				Rock->SetPosition(0,Vector(GetPosition()));
				GetParent()->Apply(0,Rock);
			}
		}
		SetName("DeadRock");
		explotion = rand()%3;
		Apply(ExplotionMaterial[explotion]);
		Geometry *geo = GetCreatorGeometry();
		geo->SetVector(0,Vector(geo->GetVector(0))*3);
		geo->SetVector(1,Vector(geo->GetVector(1))*3);
		geo->SetVector(2,Vector(geo->GetVector(2))*3);
		geo->SetVector(3,Vector(geo->GetVector(3))*3);
		exploding = true;

//		caller->Kill();
//		Kill();

	}//else
	//	if(strcmp(caller->GetName(),"Background"))
	//	if(strcmp(caller->GetName(),"Rock"))
	//	printf("%s\n",caller->GetName());
	return false;
}
