
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
//#include <Interface/Debug.h>
#include "Sparcle.h"
#include <3dapi/Geometry.h>
#include <3dapi/IndexedPolygon.h>
#include "Flare.h"
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/Vertex.h>
#include <Interface/String.h>

//Fireball::Fireball(Geometry *g, PlayerAI *m) : Intelligence(g){

inline float rnd(void){
	return(float(rand()%0xff)/255.0f);
}

Material *shot = 0;

Sparcle::Sparcle(Flare *m){
	if(!shot){
		shot = new Material("Textures/shot",Texture::cARGB);
		shot->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	}
	Geometry *g = new Geometry();
g->SetName(0,String("Sparcle"));	// fixme: Optimize!
	g->Apply(shot);
	g->Add(Vector(-3000, 3000,0));
	g->Add(Vector( 3000, 3000,0));
	g->Add(Vector( 3000,-3000,0));
	g->Add(Vector(-3000,-3000,0));
	g->Add(Vertex(0,0,0));
	g->Add(Vertex(1,1,0));
	g->Add(Vertex(2,1,1));
	g->Add(Vertex(3,0,1));
//	IndexedPolygon *pol = new IndexedPolygon(g);
	IndexedPolygon *pol = g->NewIndexedPolygon();
	pol->Add(0);
	pol->Add(1);
	pol->Add(2);
	pol->Add(3);
	pol = g->NewIndexedPolygon();
	pol->Add(3);
	pol->Add(2);
	pol->Add(1);
	pol->Add(0);
	Intelligence::Apply(g);
	g->Node::Apply(0,this);

	parent = m;
	parent->GetParent()->Apply(0,g);

	Spawn = -1.0;
	float a = rnd()*2.0f*3.14159265358979323846264338327950f;
	float b = rnd()*3.14159265358979323846264338327950f;
	float r = float(1.0f * cos(b));
	// Random spawn
	SetPosition(Vector(parent->GetPosition())+Vector(r*cos(a),r*sin(a),1.0f*sin(b)));
	// Damp velocity to get a flare tale.
	Velocity = Vector(parent->GetVelocity())*.95f;
	// Exploding velocity
	Velocity = (Vector(GetPosition())-Vector(parent->GetPosition())) * 40000.0f + Velocity;
//printf("Hi!\n");
}

Sparcle::~Sparcle(){
}

bool Sparcle::Tick(double time){
	if(Spawn<0) Spawn = oldtime = time;
	if(time-Spawn>.5f) Kill();

	double pulse = time-oldtime;
	oldtime = time;

	SetPosition(Vector(GetPosition())+Velocity*pulse);

	//c->color.g *= 0.85 ;
	//if( c->color.g < 1 ) c->color.r *= 0.90 ;
	return true;
}


    

