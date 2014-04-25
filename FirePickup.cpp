
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include <3dapi/GeoMath.h>
#include "FirePickup.h"
#include <3dapi/Geometry.h>
#include <3dapi/Camera.h>
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/IndexedPolygon.h>
#include <3dapi/Vertex.h>
#include <string.h>
#include <Interface/String.h>

//static Material *mat = 0;

FirePickup::FirePickup(Camera *cam, Geometry *c) : Intelligence(c) ,KernelClient(){

	camera = cam;
	c->SetName(0,"Pickup");

	c->Add(Vector(-200, 200,0));
	c->Add(Vector( 200, 200,0));
	c->Add(Vector( 200,-200,0));
	c->Add(Vector(-200,-200,0));
	c->Add(Vertex(0,0,0));
	c->Add(Vertex(1,1,0));
	c->Add(Vertex(2,1,1));
	c->Add(Vertex(3,0,1));
//	if(!mat){
		mat=new Material("Textures/Shield/Pickup/ShieldPickup",Texture::cARGB);//tv4logo/tv4logo");
		mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
//	}
	c->Apply(mat); //AddonMaterial);
	IndexedPolygon *pol = c->NewIndexedPolygon();
	pol->Add(3);
	pol->Add(2);
	pol->Add(1);
	pol->Add(0);
//	pol = c->NewIndexedPolygon();
//	pol->Add(0);
//	pol->Add(1);
//	pol->Add(2);
//	pol->Add(3);
	KillMe=false;
	StartTime = -1.0f;

	SetName(String("FirePickup"));
}
FirePickup::~FirePickup(){
	delete mat;
}

bool FirePickup::Tick(double time){
	if(StartTime<0.0f) StartTime=time;
	if(KillMe||time-StartTime>5.0f){
		Kill();
		return false;
	}
	Vector pos = Vector(GetPosition());
//	Geometry *geo = GetGeometry("Player1");
//	if(geo) pos-=Vector(geo->GetPosition());	// fixme: bug! geo is 0 sometimes
//	Node *n = GetNode("Camera");
	pos-=Vector(camera->GetPosition());	// fixme: bug! geo is 0 sometimes
	if(pos.X> 6400*2) SetPosition(Vector(GetPosition())-Vector(6400*2*2,0,0));
	if(pos.X<-6400*2) SetPosition(Vector(GetPosition())+Vector(6400*2*2,0,0));
	if(pos.Y> 4800*2) SetPosition(Vector(GetPosition())-Vector(0,4800*2*2,0));
	if(pos.Y<-4800*2) SetPosition(Vector(GetPosition())+Vector(0,4800*2*2,0));

	int framecount = mat->GetTexture()->GetFrameCount();
	if(framecount) mat->GetTexture()->SetFrame(((int)((time-StartTime)*framecount/2.0f))%framecount);

	return true;
}

bool FirePickup::BoundingSphereIntersection(float sqrdist, class Node *caller){
//	if(!strcmp(caller->GetName(),"Player1")){
//		SendMessage(GetHook("doublerate"),0);
//		Kill=true;
//	}
	return false;
}
