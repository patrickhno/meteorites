
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include <posix/stdio.h>
#include <3dapi/Texture.h>
#include <3dapi/Material.h>
#include <3dapi/Geometry.h>
#include <3dapi/IndexedPolygon.h>
#include <3dapi/Vertex.h>
#include "Shield.h"

ShieldAI::ShieldAI(Geometry *parent){ // : Intelligence(c){ // ,KernelClient(){

	geo = new Geometry();
	geo->SetName(0,"Shield");

	Shield1 = new Material("Textures/Ship/RStrobe",Texture::cRGB);//"Textures/Shield1/Shield",Texture::cRGB);
	Shield2 = new Material("Textures/Ship/BStrobe",Texture::cRGB);//"Textures/Shield2/Shield",Texture::cRGB);
//	Shield3 = new Material("Textures/Shield3/Shield",Texture::cRGB);
//	Shield4 = new Material("Textures/Shield/Shield",TEXTURE_RGB);
	Shield1->SetMode(MATERIAL_DEST_ADD_SOURCE);
	Shield2->SetMode(MATERIAL_DEST_ADD_SOURCE);
//	Shield3->SetMode(MATERIAL_DEST_ADD_SOURCE);
//	Shield4->SetMode(MATERIAL_DEST_ADD_SOURCE);
	Shield1->CacheAll();
	Shield2->CacheAll();

	geo->Add(Vector(-250,-250,0));
	geo->Add(Vector( 250,-250,0));
	geo->Add(Vector( 250, 250,0));
	geo->Add(Vector(-250, 250,0));
	geo->Add(Vertex(0,0,0));
	geo->Add(Vertex(1,1,0));
	geo->Add(Vertex(2,1,1));
	geo->Add(Vertex(3,0,1));

	IndexedPolygon *pol;
	pol = new IndexedPolygon(geo);
	pol->Apply(Shield1);
	pol->Add(3);
	pol->Add(2);
	pol->Add(1);
	pol->Add(0);
	pol = new IndexedPolygon(geo);
	pol->Apply(Shield2);
	pol->Add(3);
	pol->Add(2);
	pol->Add(1);
	pol->Add(0);
//	pol = new IndexedPolygon(c);
//	pol->Apply(Shield3);
//	pol->Add(3);
//	pol->Add(2);
//	pol->Add(1);
//	pol->Add(0);

//	pol = c->NewIndexedPolygon();
//	pol->Apply(Shield4);
//	pol->Add(3);
//	pol->Add(2);
//	pol->Add(1);
//	pol->Add(0);

	ColTime = -1.0f;
	StartTime = -1.0f;
	activate = true;
	Activated = -1.0f;

	pol1 = 0;

	Intelligence::Apply(geo);
	geo->Node::Apply(0,this);
	parent->Node::Apply(0,geo);
	SetPosition(Vector(0,0,0));
}

ShieldAI::~ShieldAI(){
	delete Shield1;
	delete Shield2;
//	delete Shield3;
//	delete Shield4;
	if(pol1){
		delete pol1;	// fixme: BUG! pol1 is invalid sometimes
		delete pol2;
		delete pol3;
	}
}

bool ShieldAI::Tick(double time){
//printf("!!!!!!!!\n");

	if(StartTime<0) StartTime = time;
	if(ColTime<0) ColTime = time;
	if(activate){
		Activated = time;
/*
		if(!pol1){
			pol1 = new IndexedPolygon(geo);
			pol1->Apply(Shield1);
			pol1->Add(3);
			pol1->Add(2);
			pol1->Add(1);
			pol1->Add(0);
			pol2 = new IndexedPolygon(geo);
			pol2->Apply(Shield2);
			pol2->Add(3);
			pol2->Add(2);
			pol2->Add(1);
			pol2->Add(0);
//			pol3 = new IndexedPolygon(geo);
//			pol3->Apply(Shield3);
//			pol3->Add(3);
//			pol3->Add(2);
//			pol3->Add(1);
//			pol3->Add(0);
		}
*/
	}
	activate = false;

	if(time-Activated<10.0f){

		float trans;
		if((time-ColTime)<.9f) trans = 1.0f-(time-ColTime); //Shield1->SetTranslusency(1.0f-(time-ColTime));
		else trans = .1f; //Shield1->SetTranslusency(.1f);

		int _t = (int((time-StartTime)*10000.0f))&0xffff;
		float t = (float(_t)/0xffff)*3;
		float t1 = 1.0f-t;
		float t2 = 1.0f-fabs(t-1.0f);
		float t3 = 1.0f-fabs(t-2.0f);
		if(t1<0) t1=0;
		if(t2<0) t2=0;
		if(t3<0) t3=0;
	//trans = 1.0f;
		Shield1->SetTransparency(1.0f-(t1*trans));
		Shield2->SetTransparency(1.0f-(t2*trans));
//		Shield3->SetTransparency(1.0f-(t3*trans));
	//	printf("%f,%f\n",t,t1);

		int framecount = Shield1->GetTexture()->GetFrameCount();
		int frame = int((time+.5f)*framecount/0.31f)%framecount;
	//	int sframecount = Shield4->GetTexture()->GetFrameCount();
	//	int sframe = int((time+.5f)*sframecount/(0.31f*2.0f))%sframecount;
		Shield1->GetTexture()->SetFrame(frame);
		Shield2->GetTexture()->SetFrame(frame);
//		Shield3->GetTexture()->SetFrame(frame);
	//	Shield4->GetTexture()->SetFrame(sframe);
	}else if(pol1){
		//int framecount = Shield1->GetTexture()->GetFrameCount();
		//Shield1->GetTexture()->SetFrame(0);
		//Shield2->GetTexture()->SetFrame(0);
		//Shield3->GetTexture()->SetFrame(0);
		//Shield1->SetTransparency(1);
		//Shield2->SetTransparency(1);
		//Shield3->SetTransparency(1);

		delete pol1;
		delete pol2;
//		delete pol3;
		pol1=0;
	}

	return true;
}

void ShieldAI::Collide(double time){
	ColTime = time;
}

void ShieldAI::Activate(void){
	activate = true;
/*
	if(!pol1){
		pol1 = new IndexedPolygon(geo);
		pol1->Apply(Shield1);
		pol1->Add(3);
		pol1->Add(2);
		pol1->Add(1);
		pol1->Add(0);
		pol2 = new IndexedPolygon(geo);
		pol2->Apply(Shield2);
		pol2->Add(3);
		pol2->Add(2);
		pol2->Add(1);
		pol2->Add(0);
		pol3 = new IndexedPolygon(geo);
		pol3->Apply(Shield3);
		pol3->Add(3);
		pol3->Add(2);
		pol3->Add(1);
		pol3->Add(0);
	}
*/
}

void ShieldAI::Deactivate(void){
	activate = false;
/*	if(pol1){
		delete pol1;
		delete pol2;
		delete pol3;
		pol1=0;
	}
*/
}

bool ShieldAI::Active(void){
	return pol1!=0;
}

