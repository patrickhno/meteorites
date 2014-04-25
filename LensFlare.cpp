
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
#include "LensFlare.h"

LensFlare::LensFlare(Camera *cam, class Geometry *parent){
	camera = cam;
	mat = new Material("Textures/Lens/Sun",Texture::cRGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_ADD_SOURCE); //MULTIPLY_ONE_MINUS_ALPHA);
	ring1 = new Material("Textures/Lens/Ring",Texture::cRGB);
	ring1->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_ADD_SOURCE); //MULTIPLY_ONE_MINUS_ALPHA);
	ring2 = new Material("Textures/Lens/Ring",Texture::cRGB);
	ring2->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_ADD_SOURCE); //MULTIPLY_ONE_MINUS_ALPHA);
	ring3 = new Material("Textures/Lens/Ring",Texture::cRGB);
	ring3->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_ADD_SOURCE); //MULTIPLY_ONE_MINUS_ALPHA);
	//ring->SetTransparency(.95f);
	halo = new Material("Textures/Lens/Halo",Texture::cRGB);
	halo->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_ADD_SOURCE); //MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	Geometry *g = new Geometry();
	geo = g;
	g->SetName(0,"LensFlare");
	g->Apply(mat);
	g->Add(Vector(-6000*5/2/3, 6000*5/2/3,0));
	g->Add(Vector( 6000*5/2/3, 6000*5/2/3,0));
	g->Add(Vector( 6000*5/2/3,-6000*5/2/3,0));
	g->Add(Vector(-6000*5/2/3,-6000*5/2/3,0));
	g->Add(Vector(-6000*2, 6000*2,0));
	g->Add(Vector( 6000*2, 6000*2,0));
	g->Add(Vector( 6000*2,-6000*2,0));
	g->Add(Vector(-6000*2,-6000*2,0));
	g->Add(Vector(-600, 600,0));
	g->Add(Vector( 600, 600,0));
	g->Add(Vector( 600,-600,0));
	g->Add(Vector(-600,-600,0));
	g->Add(Vector(-600, 600,0));
	g->Add(Vector( 600, 600,0));
	g->Add(Vector( 600,-600,0));
	g->Add(Vector(-600,-600,0));

	g->Add(Vector(-8000, 8000,0));
	g->Add(Vector( 8000, 8000,0));
	g->Add(Vector( 8000,-8000,0));
	g->Add(Vector(-8000,-8000,0));
	g->Add(Vector(-4000, 4000,0));
	g->Add(Vector( 4000, 4000,0));
	g->Add(Vector( 4000,-4000,0));
	g->Add(Vector(-4000,-4000,0));
	g->Add(Vector(-2000, 2000,0));
	g->Add(Vector( 2000, 2000,0));
	g->Add(Vector( 2000,-2000,0));
	g->Add(Vector(-2000,-2000,0));
	g->Add(Vector(-3000, 3000,0));
	g->Add(Vector( 3000, 3000,0));
	g->Add(Vector( 3000,-3000,0));
	g->Add(Vector(-3000,-3000,0));

	g->Add(Vertex( 0,0,0));
	g->Add(Vertex( 1,1,0));
	g->Add(Vertex( 2,1,1));
	g->Add(Vertex( 3,0,1));
	g->Add(Vertex( 4,0,0));
	g->Add(Vertex( 5,1,0));
	g->Add(Vertex( 6,1,1));
	g->Add(Vertex( 7,0,1));
	g->Add(Vertex( 8,0,0));
	g->Add(Vertex( 9,1,0));
	g->Add(Vertex(10,1,1));
	g->Add(Vertex(11,0,1));
	g->Add(Vertex(12,0,0));
	g->Add(Vertex(13,1,0));
	g->Add(Vertex(14,1,1));
	g->Add(Vertex(15,0,1));

	g->Add(Vertex(16,0,0));
	g->Add(Vertex(17,1,0));
	g->Add(Vertex(18,1,1));
	g->Add(Vertex(19,0,1));
	g->Add(Vertex(20,0,0));
	g->Add(Vertex(21,1,0));
	g->Add(Vertex(22,1,1));
	g->Add(Vertex(23,0,1));
	g->Add(Vertex(24,0,0));
	g->Add(Vertex(25,1,0));
	g->Add(Vertex(26,1,1));
	g->Add(Vertex(27,0,1));
	g->Add(Vertex(28,0,0));
	g->Add(Vertex(29,1,0));
	g->Add(Vertex(30,1,1));
	g->Add(Vertex(31,0,1));

	IndexedPolygon *pol;
	pol = new IndexedPolygon(g); //new IndexedPolygon(g);
	pol->Add(0);
	pol->Add(1);
	pol->Add(2);
	pol->Add(3);
	pol = new IndexedPolygon(g);
	pol->Apply(ring1);
	pol->Add(4);
	pol->Add(5);
	pol->Add(6);
	pol->Add(7);
	pol = new IndexedPolygon(g);
	pol->Apply(ring3);
	pol->Add(8);
	pol->Add(9);
	pol->Add(10);
	pol->Add(11);
	pol = new IndexedPolygon(g);
	pol->Apply(halo);
	pol->Add(12);
	pol->Add(13);
	pol->Add(14);
	pol->Add(15);

	pol = new IndexedPolygon(g);
	pol->Apply(ring2);
	pol->Add(16);
	pol->Add(17);
	pol->Add(18);
	pol->Add(19);
	pol = new IndexedPolygon(g);
	pol->Apply(ring2);
	pol->Add(20);
	pol->Add(21);
	pol->Add(22);
	pol->Add(23);
	pol = new IndexedPolygon(g);
	pol->Apply(ring1);
	pol->Add(24);
	pol->Add(25);
	pol->Add(26);
	pol->Add(27);
	pol = new IndexedPolygon(g);
	pol->Apply(ring3);
	pol->Add(28);
	pol->Add(29);
	pol->Add(30);
	pol->Add(31);
	Intelligence::Apply(g);
//	g->Node::Apply(this);
	g->Node::Apply(0,this);
	parent->Node::Apply(0,g);
	SetPosition(Vector(0,0,50000));
g->SetSquareRadius(0);
}

LensFlare::~LensFlare(){
	delete mat;
	delete ring1;
	delete ring2;
//fixme:	delete ring3;
	delete halo;
}

bool LensFlare::Tick(double time){
//	Node *n = GetNode(String("Camera"));	// fixme: Optimize!
	bool redo = true;
	while(redo){
		redo = false;
//		if(n){ 	// fixme: bug! n is 0 sometimes
			Vector pos = Vector(GetPosition())-Vector(camera->GetPosition());
			#if 0
			float lt = ((pos.X*pos.X+pos.Y*pos.Y)/20000000000.0f);
			float t = (((pos.X*pos.X+pos.Y*pos.Y)-(/*10000000.0f+*/pos.Z*800))/5000000.0f);
			#else
			float lt = ((pos.X*pos.X+pos.Y*pos.Y)/100000000000.0f);
			//float ti = (((pos.X*pos.X+pos.Y*pos.Y)-(/*10000000.0f+*/pos.Z*600))/5000000.0f);	// inner
			//float to = (((pos.X*pos.X+pos.Y*pos.Y)-(/*10000000.0f+*/pos.Z*800))/5000000.0f);	// outer
			//float t = ti+(to-ti)*pos.Z;
			float t = (((pos.X*pos.X+pos.Y*pos.Y)-(pos.Z*800-1000000.0f))/5000000.0f);	// outer
			#endif
			//printf("%f\n",t);
			if(t>1) t = 1;
			if(t<0) t = 0;
			if(lt>1) lt = 1;
			if(lt<0) lt = 0;
			mat->SetTransparency(1-t);
/*
			ring1->SetTransparency(ARGB(1-(.03f-lt)*t*( 33.0f/48.0f),
										1-(.03f-lt)*t*( 29.0f/48.0f),
										1-(.03f-lt)*t*(  4.0f/48.0f)));
			ring2->SetTransparency(ARGB(1-(.03f-lt)*t*( 48.0f/48.0f),
										1-(.03f-lt)*t*( 38.0f/48.0f),
										1-(.03f-lt)*t*( 18.0f/48.0f)));
			ring3->SetTransparency(ARGB(1-(.03f-lt)*t*( 34.0f/72.0f),
										1-(.03f-lt)*t*( 30.0f/72.0f),
										1-(.03f-lt)*t*( 72.0f/72.0f)));
*/
			ring1->SetTransparency(ARGB(1-(.03f-lt)*t*( 33.0f*1.5f/48.0f),
										1-(.03f-lt)*t*( 29.0f*1.5f/48.0f),
										1-(.03f-lt)*t*(  4.0f*1.5f/48.0f)));
			ring2->SetTransparency(ARGB(1-(.03f-lt)*t*( 48.0f*1.5f/48.0f),
										1-(.03f-lt)*t*( 38.0f*1.5f/48.0f),
										1-(.03f-lt)*t*( 18.0f*1.5f/48.0f)));
			ring3->SetTransparency(ARGB(1-(.03f-lt)*t*( 34.0f*1.5f/72.0f),
										1-(.03f-lt)*t*( 30.0f*1.5f/72.0f),
										1-(.03f-lt)*t*( 72.0f*1.5f/72.0f)));


			//ring->SetTransparency((1-(.03f-lt)*t));
			halo->SetTransparency(1-(.5f-(lt*10))*t);

// 33,29,4
// 48,38,18
// 34,30,72

//ring->SetDiffuseColor(ARGB(33.0f/100.0f,29.0f/100.0f,4.0f/100.0f));

	geo->SetVector( 4,Vector(-6000*2, 6000*2,pos.Z*2)-(pos*2));
	geo->SetVector( 5,Vector( 6000*2, 6000*2,pos.Z*2)-(pos*2));
	geo->SetVector( 6,Vector( 6000*2,-6000*2,pos.Z*2)-(pos*2));
	geo->SetVector( 7,Vector(-6000*2,-6000*2,pos.Z*2)-(pos*2));
	geo->SetVector( 8,Vector(-6000, 6000,pos.Z*5)-(pos*5));
	geo->SetVector( 9,Vector( 6000, 6000,pos.Z*5)-(pos*5));
	geo->SetVector(10,Vector( 6000,-6000,pos.Z*5)-(pos*5));
	geo->SetVector(11,Vector(-6000,-6000,pos.Z*5)-(pos*5));
	geo->SetVector(12,Vector(-600, 600,pos.Z*1)-(pos*1));
	geo->SetVector(13,Vector( 600, 600,pos.Z*1)-(pos*1));
	geo->SetVector(14,Vector( 600,-600,pos.Z*1)-(pos*1));
	geo->SetVector(15,Vector(-600,-600,pos.Z*1)-(pos*1));

	geo->SetVector(16,Vector(-8000, 8000,pos.Z*6)-(pos*6));
	geo->SetVector(17,Vector( 8000, 8000,pos.Z*6)-(pos*6));
	geo->SetVector(18,Vector( 8000,-8000,pos.Z*6)-(pos*6));
	geo->SetVector(19,Vector(-8000,-8000,pos.Z*6)-(pos*6));
	geo->SetVector(20,Vector(-4000, 4000,pos.Z*3)-(pos*3));
	geo->SetVector(21,Vector( 4000, 4000,pos.Z*3)-(pos*3));
	geo->SetVector(22,Vector( 4000,-4000,pos.Z*3)-(pos*3));
	geo->SetVector(23,Vector(-4000,-4000,pos.Z*3)-(pos*3));
	geo->SetVector(24,Vector(-2000, 2000,pos.Z*4)-(pos*4));
	geo->SetVector(25,Vector( 2000, 2000,pos.Z*4)-(pos*4));
	geo->SetVector(26,Vector( 2000,-2000,pos.Z*4)-(pos*4));
	geo->SetVector(27,Vector(-2000,-2000,pos.Z*4)-(pos*4));
	geo->SetVector(28,Vector(-3000, 3000,pos.Z*1.5f)-(pos*1.5f));
	geo->SetVector(29,Vector( 3000, 3000,pos.Z*1.5f)-(pos*1.5f));
	geo->SetVector(30,Vector( 3000,-3000,pos.Z*1.5f)-(pos*1.5f));
	geo->SetVector(31,Vector(-3000,-3000,pos.Z*1.5f)-(pos*1.5f));

//	geo->SetColor(4,ARGB(33.0f/100.0f,29.0f/100.0f,4.0f/100.0f));
//	geo->SetColor(5,ARGB(33.0f/100.0f,29.0f/100.0f,4.0f/100.0f));
//	geo->SetColor(6,ARGB(33.0f/100.0f,29.0f/100.0f,4.0f/100.0f));
//	geo->SetColor(7,ARGB(33.0f/100.0f,29.0f/100.0f,4.0f/100.0f));

			if(pos.X> 7000*3*4){ SetPosition(Vector(GetPosition())-Vector(7000*6*4,0,0)); redo = true; }
			if(pos.X<-7000*3*4){ SetPosition(Vector(GetPosition())+Vector(7000*6*4,0,0)); redo = true; }
			if(pos.Y> 7000*3*4){ SetPosition(Vector(GetPosition())-Vector(0,7000*6*4,0)); redo = true; }
			if(pos.Y<-7000*3*4){ SetPosition(Vector(GetPosition())+Vector(0,7000*6*4,0)); redo = true; }
//		}
	}
	return true;
}

