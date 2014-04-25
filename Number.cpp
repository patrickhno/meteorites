
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <Interface/Debug.h>
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/Geometry.h>
#include <3dapi/Camera.h>
#include <3dapi/IndexedPolygon.h>
#include <3dapi/Vertex.h>
#include "Number.h"
#include "Player.h"
#include <posix/stdio.h>

Number::Number(Camera *cam, PlayerAI *_ship, int n){
	camera = cam;
	ship = _ship;
	char str[1024];
	sprintf(str,"Textures/interface/playernum/no%d",n+1);
	mat = new Material(str,Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();

	Geometry *g = new Geometry();
	g->Apply(mat);
	g->Add(Vector(-200, 200,0));
	g->Add(Vector( 200, 200,0));
	g->Add(Vector( 200,-200,0));
	g->Add(Vector(-200,-200,0));
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

	Intelligence::Apply(g);
	g->Node::Apply(0,this);
	ship->GetCreatorGeometry()->Node::Apply(0,g);
//	SetOrientation(-Quaternion(ship->GetOrientation())*-Quaternion(camera->GetOrientation()));
	SetOrientation(-Quaternion(camera->GetOrientation())*-Quaternion(ship->GetOrientation()));
	OldTime = -1;
	trans = -2;
}

Number::~Number(){
	delete mat;
}

void Number::Activate(void){
	//active = state;
	trans = 0;
}

bool Number::Tick(double time){
//	if(active) mat->SetTransparency(0);
//	else mat->SetTransparency(1);
	if(OldTime<0) OldTime = time;
	float pulse = time-OldTime;
	OldTime = time;
	if(pulse>0){
		trans+=pulse;
		if(trans>1) trans = 1;
//printf("%f\n",trans);
		mat->SetTransparency(trans);
//		SetOrientation(-Quaternion(ship->GetOrientation())*-Quaternion(camera->GetOrientation()));
		SetOrientation(-Quaternion(camera->GetOrientation())*-Quaternion(ship->GetOrientation()));
	}
	SetPosition(Vector(0,0,0));
	return true;
}

