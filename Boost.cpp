#if 0

// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
//#include <Interface/Debug.h>

#include "Boost.h"
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/Geometry.h>
#include <3dapi/IndexedPolygon.h>
#include <assert.h>

BoostAI::BoostAI(Geometry *c, Geometry *_ship) : Intelligence(c){ // ,KernelClient(){

	geo = c;
	c->SetName(0,"Boost");

	ship = _ship;
	Boost  = new Material("Textures/Boost/Flame",Texture::cRGB);
	Boost->SetMode(MATERIAL_DEST_ADD_SOURCE|MATERIAL_SOURCE_DIFFUSE);
	Boost->CacheAll();

	c->Apply(Boost);

	c->Add(Vector(-5*4,-20*4,0));
	c->Add(Vector( 5*4,-20*4,0));
	c->Add(Vector( 5*4, 20*4,0));
	c->Add(Vector(-5*4, 20*4,0));
	c->Add(Vertex(0,0,0));
	c->Add(Vertex(1,1,0));
	c->Add(Vertex(2,1,1));
	c->Add(Vertex(3,0,1));

	IndexedPolygon *pol;
	pol = c->NewIndexedPolygon();
	pol->Add(0);
	pol->Add(1);
	pol->Add(2);
	pol->Add(3);
	pol = c->NewIndexedPolygon();
	pol->Add(3);
	pol->Add(2);
	pol->Add(1);
	pol->Add(0);

	OldVelocity = Vector(0,0,0);

	pol = 0;
	Activate();
}

BoostAI::~BoostAI(){
	delete Boost;
}

bool BoostAI::Tick(double time){
	int framecount = GetCreatorGeometry()->GetMaterial()->GetTexture()->GetFrameCount();
	int frame = rand()%(framecount-1);
	if(framecount) GetCreatorGeometry()->GetMaterial()->GetTexture()->SetFrame(frame);

//	Geometry *geo = GetGeometry("Player1");
//	if(geo){
//		float val = (Vector(ship->GetIntelligence()->GetVelocity())-OldVelocity).Lenght();
		Intelligence *ai = ship->GetIntelligence();
		if(ai){
			Vector vel = Vector(ai->GetVelocity());
			vel-=OldVelocity;
			float val = vel.Lenght()*2.0f;
			OldVelocity = Vector(ship->GetIntelligence()->GetVelocity());
			if(val<200){
				SetVector(2,Vector( 5*4, val-20,0));
				SetVector(3,Vector(-5*4, val-20,0));
			}
		}
//	}

	return true;
}

void BoostAI::Activate(void){
	assert(pol==0);
	pol = new IndexedPolygon(geo);
	pol->Add(3);
	pol->Add(2);
	pol->Add(1);
	pol->Add(0);
}

void BoostAI::Deactivate(void){
	if(pol) delete pol;
	pol = 0;
}

#endif
