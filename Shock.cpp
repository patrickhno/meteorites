
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/Geometry.h>
#include <3dapi/IndexedPolygon.h>
#include <3dapi/Vertex.h>
#include "Shock.h"
#include "Player.h"

Shock::Shock(class PlayerAI *player, Vector &direction){

	mat = new Material("Textures/Shield/Shield",Texture::cARGB);
	mat->SetMode(MATERIAL_DEST_ADD_SOURCE);
	Geometry *g = new Geometry();
	g->SetName(0,"Shock");
	g->Apply(mat);
	g->Add(Vector(-25000, 25000,0));
	g->Add(Vector( 25000, 25000,0));
	g->Add(Vector( 25000,-25000,0));
	g->Add(Vector(-25000,-25000,0));
	g->Add(Vertex(0,0,0));
	g->Add(Vertex(1,1,0));
	g->Add(Vertex(2,1,1));
	g->Add(Vertex(3,0,1));
	IndexedPolygon *pol;
	pol = g->NewIndexedPolygon(); //new IndexedPolygon(g);
	pol->Add(0);
	pol->Add(1);
	pol->Add(2);
	pol->Add(3);
	Intelligence::Apply(g);
	g->Node::Apply(0,this);
	player->GetCreatorGeometry()->Node::Apply(0,g);
	SetPosition(Vector(0,0,0));
	Quaternion dir = Quaternion(direction.X,-direction.Y,0,0);
	SetOrientation(Quaternion(dir));
	Spawn = -1.0f;
}

Shock::~Shock(){
	delete mat;
}

bool Shock::Tick(double time){
	if(Spawn<0) Spawn = time;
	int framecount = mat->GetTexture()->GetFrameCount();
	int frame = int((time-Spawn)*float(framecount)/1.0f)%framecount;
	mat->GetTexture()->SetFrame(frame);
	if(time-Spawn>1.0f) Kill();
	return true;
}


