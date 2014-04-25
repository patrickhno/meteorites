#if 0

// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/Geometry.h>
#include <3dapi/IndexedPolygon.h>
#include <assert.h>
#include "BlueStrobe.h"

BlueStrobeAI::BlueStrobeAI(Geometry *c) : Intelligence(c){ // ,KernelClient(){

	geo = c;

	c->SetName(0,"BlueStrobe");

	BlueStrobe  = new Material("Textures/Ship/BStrobe",Texture::cRGB);
//	BlueStrobe = new Material("Textures/Ship/BlueStrobe");
	BlueStrobe->SetMode(MATERIAL_DEST_ADD_SOURCE);
//	BlueStrobe->CacheAll();

	c->Apply(BlueStrobe);

	c->Add(Vector(-200,-200,0));
	c->Add(Vector( 200,-200,0));
	c->Add(Vector( 200, 200,0));
	c->Add(Vector(-200, 200,0));
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

	pulse = 0.3f+float(rand())/1000000.0f;
	pol = 0;
	Activate();
}

BlueStrobeAI::~BlueStrobeAI(){
	delete BlueStrobe;
}

bool BlueStrobeAI::Tick(double time){
	int framecount = GetCreatorGeometry()->GetMaterial()->GetTexture()->GetFrameCount();
	int frame = ((int)(time*framecount/pulse))%(framecount*4);
	if(frame>=framecount) frame=0;
	if(framecount) GetCreatorGeometry()->GetMaterial()->GetTexture()->SetFrame(frame);
	return true;
}

void BlueStrobeAI::Activate(void){
	assert(pol==0);
	pol = new IndexedPolygon(geo);
	pol->Add(3);
	pol->Add(2);
	pol->Add(1);
	pol->Add(0);
}

void BlueStrobeAI::Deactivate(void){
	if(pol) delete pol;
	pol = 0;
}

#endif
