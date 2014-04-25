
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include <posix/stdio.h>
#include <3dapi/Node.h>
#include <3dapi/Geometry.h>
#include <3dapi/IndexedPolygon.h>
#include <3dapi/Texture.h>
#include <3dapi/Material.h>
#include <3dapi/Camera.h>
#include <3dapi/Vertex.h>
#include <Interface/String.h>
#include "Background.h"

#define tiles 7

Background::Background(Camera *cam, Geometry *c) : Intelligence(c){ // ,KernelClient(){

	camera = cam;
	c->SetName(0,String("Background"));

	for(int y=0; y<tiles*2; y++){
		for(int x=0; x<tiles*2; x++){
			c->Add(Vector((-6400.0f*tiles+x*6400.0f*(tiles*2.0f)/(tiles*2))*2,(-6400.0f*tiles+y*6400.0f*(tiles*2.0f)/(tiles*2))*2,0));
		}
	}

	IndexedPolygon *pol;
	int vx=0;
	for(y=0; y<tiles*2-1; y++){
		for(int x=0; x<tiles*2-1; x++){
			float u=(x*tiles)/(tiles*2.0f);
			float v=(y*tiles)/(tiles*2.0f);
			while(u>=.0f) u-=1.0f;
			while(v>=.0f) v-=1.0f;
			u+=1.0f;
			v+=1.0f;
			pol = c->NewIndexedPolygon();
			pol->Add(vx++);
			c->Add(Vertex(y*(tiles*2)+x            ,u          ,v));
			pol->Add(vx++);
			c->Add(Vertex(y*(tiles*2)+x+1          ,u+tiles/(tiles*2.0f),v));
			pol->Add(vx++);
			c->Add(Vertex(y*(tiles*2)+x+1+(tiles*2),u+tiles/(tiles*2.0f),v+tiles/(tiles*2.0f)));
			pol->Add(vx++);
			c->Add(Vertex(y*(tiles*2)+x+(tiles*2)  ,u          ,v+tiles/(tiles*2.0f)));
		}
	}

	BackMaterial = new Material("Textures/Background",Texture::cRGB);
//	BackMaterial->CacheAll();
	c->Apply(BackMaterial);
c->SetSquareRadius(0);
}

Background::~Background(){
	delete BackMaterial;
}

bool Background::Tick(double time){
	bool redo = true;
	Vector orgpos    = Vector(GetPosition());
	Vector orgcampos = Vector(camera->GetPosition());
	Vector orgofs  = Vector(GetPosition())-Vector(6400/2*2,4800/2*2,0);
	Vector orgdelta = orgofs-Vector(camera->GetPosition());
	while(redo){
		Vector pos = Vector(GetPosition())-Vector(6400/2*2,4800/2*2,0);
		redo = false;
		Vector campos = Vector(camera->GetPosition());
		pos-=campos; //Vector(camera->GetPosition());
		if(pos.X> 6400*2){ SetPosition(Vector(GetPosition())-Vector(6400*2*2,0,0)); redo = true; }
		if(pos.X<-6400*2){ SetPosition(Vector(GetPosition())+Vector(6400*2*2,0,0)); redo = true; }
		if(pos.Y> 6400*2){ SetPosition(Vector(GetPosition())-Vector(0,6400*2*2,0)); redo = true; }
		if(pos.Y<-6400*2){ SetPosition(Vector(GetPosition())+Vector(0,6400*2*2,0)); redo = true; }
	}
	return true;
}

