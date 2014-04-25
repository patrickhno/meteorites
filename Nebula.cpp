
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include "Nebula.h"
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/Geometry.h>
#include <3dapi/Camera.h>
#include <3dapi/IndexedPolygon.h>
#include <3dapi/Vertex.h>
#include <Interface/String.h>

Nebula::Nebula(class Camera *cam, class Geometry *parent){
	camera = cam;

//	mat = new Material("Textures/Backdrops/Planet5",Texture::cARGB);
//	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);

	mat = new Material("Textures/Backdrops/Nebulae",Texture::cARGB);
//	mat->SetTransparency(.8f);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
//mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_SOURCE_MULTIPLY_EMISSIVE);
	Geometry *g = new Geometry();
	g->SetName(0,"Nebula");
//	g->Apply(mat);
	g->Add(Vector(-120000, 120000,0));
	g->Add(Vector( 120000, 120000,0));
	g->Add(Vector( 120000,-120000,0));
	g->Add(Vector(-120000,-120000,0));
	g->Add(Vertex(0,0,0));
	g->Add(Vertex(1,1,0));
	g->Add(Vertex(2,1,1));
	g->Add(Vertex(3,0,1));
	IndexedPolygon *pol;
	pol = new IndexedPolygon(g); ////g->NewIndexedPolygon(); //new IndexedPolygon(g);
	pol->Add(0);
	pol->Add(1);
	pol->Add(2);
	pol->Add(3);
pol->Apply(mat);
	Intelligence::Apply(g);
	g->Node::Apply(0,this);
	parent->Node::Apply(0,g);
	SetPosition(Vector(0,0,100000));
g->SetSquareRadius(0);
}

Nebula::~Nebula(){
	delete mat;
}

bool Nebula::Tick(double time){
//	Node *n = GetNode(String("Camera"));	// fixme: Optimize!
	Vector pos = Vector(camera->GetPosition());
	pos.Z = 100000;
	SetPosition(pos);
	bool redo = true;
	while(redo){
		redo = false;
//		if(n){ 	// fixme: bug! n is 0 sometimes
			Vector pos = Vector(GetPosition())-Vector(camera->GetPosition());
			if(pos.X> 6400*3*4){ SetPosition(Vector(GetPosition())-Vector(  6400*6*4,0,0)); redo = true; }
			if(pos.X<-6400*3*4){ SetPosition(Vector(GetPosition())+Vector(  6400*6*4,0,0)); redo = true; }
			if(pos.Y> 4800*4*4){ SetPosition(Vector(GetPosition())-Vector(0,4800*8*4,0)); redo = true; }
			if(pos.Y<-4800*4*4){ SetPosition(Vector(GetPosition())+Vector(0,4800*8*4,0)); redo = true; }
//		}
	}
	return true;
}

