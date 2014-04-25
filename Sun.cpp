
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include <posix/stdio.h>
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/Geometry.h>
#include <3dapi/Camera.h>
#include <3dapi/IndexedPolygon.h>
#include <3dapi/Vertex.h>
#include <Interface/String.h>
#include "Sun.h"

Sun::Sun(Camera *cam, class Geometry *parent){
	camera = cam;
	mat1 = new Material("Textures/Lens/Halo",Texture::cRGB);
	mat1->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_ADD_SOURCE); //MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat2 = new Material("Textures/Lens/Sun",Texture::cRGB);
	mat2->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_ADD_SOURCE); //MULTIPLY_ONE_MINUS_ALPHA);
//mat1->SetTransparency(.6f);
//mat2->SetTransparency(.8f);
mat1->SetTransparency(.95f);
mat2->SetTransparency(.8f);
	Geometry *g = new Geometry();
	g->SetName(0,"Sun");
	g->Apply(mat1);
/*
	g->Add(Vector(-6000/2/3, 6000/2/3,0));
	g->Add(Vector( 6000/2/3, 6000/2/3,0));
	g->Add(Vector( 6000/2/3,-6000/2/3,0));
	g->Add(Vector(-6000/2/3,-6000/2/3,0));
	g->Add(Vector(-6000*5/2, 6000*5/2,-10000));
	g->Add(Vector( 6000*5/2, 6000*5/2,-10000));
	g->Add(Vector( 6000*5/2,-6000*5/2,-10000));
	g->Add(Vector(-6000*5/2,-6000*5/2,-10000));
*/
	g->Add(Vector(-6000*5/2, 6000*5/2,0));
	g->Add(Vector( 6000*5/2, 6000*5/2,0));
	g->Add(Vector( 6000*5/2,-6000*5/2,0));
	g->Add(Vector(-6000*5/2,-6000*5/2,0));
	g->Add(Vector(-6000*5/2, 6000*5/2,-10000));
	g->Add(Vector( 6000*5/2, 6000*5/2,-10000));
	g->Add(Vector( 6000*5/2,-6000*5/2,-10000));
	g->Add(Vector(-6000*5/2,-6000*5/2,-10000));

	g->Add(Vertex(0,0,0));
	g->Add(Vertex(1,1,0));
	g->Add(Vertex(2,1,1));
	g->Add(Vertex(3,0,1));
	g->Add(Vertex(4,0,0));
	g->Add(Vertex(5,1,0));
	g->Add(Vertex(6,1,1));
	g->Add(Vertex(7,0,1));
	IndexedPolygon *pol;

	pol = new IndexedPolygon(g); //new IndexedPolygon(g);
	pol->Add(0);
	pol->Add(1);
	pol->Add(2);
	pol->Add(3);
//pol->Apply(mat1);

/*	pol = new IndexedPolygon(g); //new IndexedPolygon(g);
	pol->Apply(mat2);
	pol->Add(4);
	pol->Add(5);
	pol->Add(6);
	pol->Add(7);*/
	Intelligence::Apply(g);
	g->Node::Apply(0,this);
	parent->Node::Apply(0,g);
	SetPosition(Vector(0,0,50000));
g->SetSquareRadius(0);
}

Sun::~Sun(){
	delete mat1;
	delete mat2;
}

bool Sun::Tick(double time){
	//Node *n = GetNode(String("Camera"));	// fixme: Optimize!
	bool redo = true;
	while(redo){
		redo = false;
		//if(n){ 	// fixme: bug! n is 0 sometimes
			Vector pos = Vector(GetPosition())-Vector(camera->GetPosition());
			//float t = (((pos.X*pos.X+pos.Y*pos.Y)-30000000.0f)/10000000.0f);
			//printf("%f\n",t);
			float t = (((pos.X*pos.X+pos.Y*pos.Y)-(/*10000000.0f+*/pos.Z*800))/5000000.0f);
			t=1-t;
			if(t<0) t = 0;
			t+=.95f;
//printf("%f\n",t);
			if(t>1) t = 1;
			mat1->SetTransparency(t);
			if(pos.X> 7000*3* 4){ SetPosition(Vector(GetPosition())-Vector(7000*6* 4,0,0)); redo = true; }
			if(pos.X<-7000*3* 4){ SetPosition(Vector(GetPosition())+Vector(7000*6* 4,0,0)); redo = true; }
			if(pos.Y> 7000*3* 4){ SetPosition(Vector(GetPosition())-Vector(0,7000*6* 4,0)); redo = true; }
			if(pos.Y<-7000*3* 4){ SetPosition(Vector(GetPosition())+Vector(0,7000*6* 4,0)); redo = true; }
		//}
	}
	return true;
}

