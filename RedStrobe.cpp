#if 0

// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
//#include <Interface/Debug.h>

#include "RedStrobe.h"
#include <3dapi/Texture.h>
#include <3dapi/Material.h>
#include <3dapi/Geometry.h>
#include <3dapi/IndexedPolygon.h>
#include <assert.h>

RedStrobeAI::RedStrobeAI(Geometry *c) : Intelligence(c){ // ,KernelClient(){

	geo = c;
	c->SetName(0,"RedStrobe");

	RedStrobe  = new Material("Textures/Ship/RStrobe",Texture::cRGB);
//	BlueStrobe = new Material("Textures/Ship/BlueStrobe");
	RedStrobe->SetMode(MATERIAL_DEST_ADD_SOURCE);
	RedStrobe->CacheAll();

	c->Apply(RedStrobe);

	c->Add(Vector(-200,-200,0));
	c->Add(Vector( 200,-200,0));
	c->Add(Vector( 200, 200,0));
	c->Add(Vector(-200, 200,0));
	c->Add(Vertex(0,0,0));
	c->Add(Vertex(1,1,0));
	c->Add(Vertex(2,1,1));
	c->Add(Vertex(3,0,1));
/*
	IndexedPolygon *pol;
//	pol = c->NewIndexedPolygon();
//	pol->Add(0);
//	pol->Add(1);
//	pol->Add(2);
//	pol->Add(3);
	pol = c->NewIndexedPolygon();
	pol->Add(3);
	pol->Add(2);
	pol->Add(1);
	pol->Add(0);
*/
	pulse = 0.3f+float(rand())/1000000.0f;
	pol = 0;
	Activate();
}

RedStrobeAI::~RedStrobeAI(){
	delete RedStrobe;
}

bool RedStrobeAI::Tick(double time){
	int framecount = GetCreatorGeometry()->GetMaterial()->GetTexture()->GetFrameCount();
	int frame = ((int)((time+.5f)*framecount/pulse))%(framecount*4);
	if(frame>=framecount) frame=0;
	if(framecount) GetCreatorGeometry()->GetMaterial()->GetTexture()->SetFrame(frame);
	return true;
}

void RedStrobeAI::Activate(void){
	assert(pol==0);
	pol = new IndexedPolygon(geo);
	pol->Add(3);
	pol->Add(2);
	pol->Add(1);
	pol->Add(0);
}

void RedStrobeAI::Deactivate(void){
	if(pol) delete pol;
	pol = 0;
}
#endif
