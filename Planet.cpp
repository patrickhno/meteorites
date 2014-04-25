
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include "Planet.h"
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/Geometry.h>
#include <3dapi/Camera.h>
#include <3dapi/IndexedPolygon.h>
#include <3dapi/Vertex.h>
#include <Interface/String.h>

/*
Sparcle::Sparcle(Flare *m){
	if(!shot){
		shot = new Material("Textures/shot",TEXTURE_ARGB);
		shot->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	}
	Geometry *g = new Geometry();
g->SetName("Sparcle");
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
	g->Node::Apply(this);

	parent = m;
	parent->GetParent()->Apply(g);

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
*/

Planet::Planet(Camera *cam, class Geometry *parent){
	camera = cam;
	mat = new Material("Textures/Backdrops/Planet5",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	Geometry *g = new Geometry();
	g->SetName(0,"Planet");
	g->Apply(mat);
	g->Add(Vector(-6000, 6000,0));
	g->Add(Vector( 6000, 6000,0));
	g->Add(Vector( 6000,-6000,0));
	g->Add(Vector(-6000,-6000,0));
	g->Add(Vertex(0,0,0));
	g->Add(Vertex(1,1,0));
	g->Add(Vertex(2,1,1));
	g->Add(Vertex(3,0,1));
	IndexedPolygon *pol;
	pol = /*g->NewIndexedPolygon();*/ new IndexedPolygon(g);
	pol->Add(0);
	pol->Add(1);
	pol->Add(2);
	pol->Add(3);
	Intelligence::Apply(g);
	g->Node::Apply(0,this);
	parent->Node::Apply(0,g);
	SetPosition(Vector(0,0,0));
g->SetSquareRadius(0);
}

Planet::~Planet(){
	delete mat;
}

bool Planet::Tick(double time){
	//Node *n = GetNode(String("Camera"));	// fixme: Optimize!
	bool redo = true;
	while(redo){
		redo = false;
//		if(n){ 	// fixme: bug! n is 0 sometimes
			Vector pos = Vector(GetPosition())-Vector(camera->GetPosition());
			if(pos.X> 7000*3){ SetPosition(Vector(GetPosition())-Vector(7000*6,0,0)); redo = true; }
			if(pos.X<-7000*3){ SetPosition(Vector(GetPosition())+Vector(7000*6,0,0)); redo = true; }
			if(pos.Y> 7000*3){ SetPosition(Vector(GetPosition())-Vector(0,7000*6,0)); redo = true; }
			if(pos.Y<-7000*3){ SetPosition(Vector(GetPosition())+Vector(0,7000*6,0)); redo = true; }
//		}
	}
	return true;
}

