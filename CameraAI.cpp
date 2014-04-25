
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include <posix/stdio.h>
#include <3dapi/Geometry.h>
#include <3dapi/Camera.h>
#include <Interface/String.h>
#include "CameraAI.h"
#include "Player.h"

CameraAI::CameraAI(Camera *c) : Intelligence(c){
	PositionStep=Vector(0,0,0);
	OldTime=-1.0f;
	PositionStep=Vector(0,0,0);
	Ofs=Vector(0,0,0);
	SetPosition(Vector(0,0,-600));
	Orientation = Euler(0,0,0);
	vel = Vector(0,0,0);
}
CameraAI::~CameraAI(){
}

bool CameraAI::Tick(double time){
//Vector p = Vector(GetPosition());
//printf("Camera (%f,%f,%f)\n",p.X,p.Y,p.Z);
	if(OldTime<0) OldTime = time;
	float pulse=(float)(time-OldTime);

	if(pulse>0){

//	Euler o = Euler(Quaternion(GetOrientation()));
		Orientation+=Euler(0,0,-.03f)*pulse;
		SetOrientation(Quaternion(Orientation));
/*
	float pulse=(float)(time-OldTime);
	Geometry *pl = GetGeometry("Player1");
	if(pl) PositionStep=Vector(pl->GetPosition())-Vector(GetPosition());
	PositionStep.Z=0;
	Vector NewPos=Vector(GetPosition())+(PositionStep*pulse);
	NewPos.Z=-70000-PositionStep.SquareLenght()/80000;	// 50000
	SetPosition(NewPos);
*/
/*
	float pulse=(float)(time-OldTime);
	Geometry *pl = GetGeometry("Player1");
	if(pl) PositionStep=Vector(pl->GetPosition())-(Vector(GetPosition())-Ofs);
	PositionStep.Z=0;
	Vector NewPos=(Vector(GetPosition())-Ofs)+(PositionStep*pulse);
	NewPos.Z=-70000-PositionStep.SquareLenght()/80000;	// 50000
	Ofs = Vector(PositionStep.X,PositionStep.Y,0);
	Ofs/=2.0f;
	SetPosition(NewPos+Ofs);
*/
/*
	float pulse=(float)(time-OldTime);
	Geometry *pl = GetGeometry("Player1");
	if(pl) PositionStep=Vector(pl->GetIntelligence()->GetVelocity());
	PositionStep*=PositionStep;
	NewPos.Z=-70000-PositionStep.SquareLenght()/1000;	// 50000
	SetPosition(NewPos);
*/
/*
	#if 0
	PositionStep=Vector(0,0,0);
	for(int n=0; n<4; n++){
		float pulse=(float)(time-OldTime);
		char name[1024];
		sprintf(name,"Player%d",n);
		Geometry *pl = GetGeometry(name);
		if(pl){
			Vector step = Vector(pl->GetPosition())-(Vector(GetPosition())-Ofs);
			PositionStep += step;
		}
	}
	PositionStep.Z=0;
	Vector NewPos=(Vector(GetPosition())-Ofs)+(PositionStep*pulse);
//	NewPos.Z=-70000-PositionStep.SquareLenght()/80000;	// 50000
//	NewPos.Z=-70000-zoom/8000000;	// 50000
	Ofs = Vector(PositionStep.X,PositionStep.Y,0);
	Ofs/=2.0f;
	SetPosition(NewPos+Ofs);

	#else

	PositionStep=Vector(0,0,0);
	int cnt=0;
	for(int n=0; n<16; n++){
		float pulse=(float)(time-OldTime);
		char name[1024];
		sprintf(name,"Player%d",n);
		Node *pl = GetNode(String(name));	// fixme: Optimize!
//printf("%x\n",pl);
		if(pl){
			if(n==0){
				Vector step = Vector(pl->GetPosition()); //-Vector(GetPosition());
				PositionStep = step;
				cnt++;
			}else{
				Vector step = Vector(pl->GetPosition()); //-Vector(GetPosition());
				PositionStep += step;
				cnt++;
			}
		}
	}
	PositionStep.Z=0;
	PositionStep/=float(cnt);
	SetPosition(PositionStep);
	#endif

	float max=0;
	for(n=0; n<16; n++){
		float pulse=(float)(time-OldTime);
		char name[1024];
		sprintf(name,"Player%d",n);
		Geometry *pl = GetGeometry(String(name));
//printf("%s\n",pl->GetName().GetString());
		if(pl){
			float len = (Vector(pl->GetPosition())-Vector(GetPosition())).SquareLenght();
			if(len>max) max=len;
		}
	}
	Vector pos = Vector(GetPosition());
//printf("%f,%f,%f\n",pos.X,pos.Y,pos.Z);
	pos.Z = -700.0f-float(sqrt(max)); ///800000;
	if(pos.Z<-10000.0f) pos.Z = -10000.0f;
//printf("%f\n",pos.Z);
	SetPosition(pos);
*/

//	float pulse=float(time-OldTime);
		Vector max = Vector(0,0,0);
		Vector CtrlA=max,CtrlB=max;
		Vector Last = max;
		PlayerAI *pl;
		int cnt = 0;
		for(int n=0; n<MAX_PLAYERS; n++){
			char name[1024];
			sprintf(name,"Player%d",n);
			Node *a = GetNode(String(name));	// fixme: Optimize!
			if(a&&((PlayerAI*)a->GetIntelligence())){
				cnt++;
				Vector A = Vector(a->GetPosition());
				Last = A;
				//if(((PlayerAI*)a->GetIntelligence())->hook){
					pl = (PlayerAI*)a->GetIntelligence();
					for(int n2=0; n2<MAX_PLAYERS; n2++){
						char name[1024];
						sprintf(name,"Player%d",n2);
						Node *b = GetNode(String(name));	// fixme: Crashed once!
						if(b&&((PlayerAI*)b->GetIntelligence())){
				//		if(b&&((PlayerAI*)b->GetIntelligence())->hook){
							Vector B = Vector(b->GetPosition());
							if((B-A)>max){
								max = B-A;
								CtrlA = A;
								CtrlB = B;
							}
						}
					}
				//}
			}
		}
		Vector oldpos,pos,newpos,plvel;
//printf("%d\n",cnt);
		switch(cnt){
		case 0:
			pos = (Vector(cos(time/15.0f)*10000,0,sin(time/15.0f)*10000-/*5000-*/15000));
//printf("%f,%f,%f\n",pos.X,pos.Y,pos.Z);
			oldpos = Vector(GetPosition());
//printf("%f,%f,%f\n",(oldpos+(pos-oldpos)*.1f).X,(oldpos+(pos-oldpos)*.1f).Y,(oldpos+(pos-oldpos)*.1f).Z);
			SetPosition(oldpos+(pos-oldpos)*.1f);
		break;
		case 1:
			//Vector pos = (CtrlA+CtrlB)/2;
			//pos.Z = CtrlA.Z-sqrt((CtrlA.X-pos.X)*(CtrlA.X-pos.X)+(CtrlA.Y-pos.Y)*(CtrlA.Y-pos.Y))*.8f;
			//Last.Z = -2000; //-((Last-oldpos)/pulse).SquareLenght()*.001f;
			oldpos = Vector(GetPosition());
			Last.Z = oldpos.Z;
			newpos = oldpos+(Last-oldpos)*.4f;
			//vel += (newpos-oldpos)/pulse;
			//vel/=2;
			//printf("%f,%f,%f,%f\n",vel.X*vel.X+vel.Y*vel.Y,pulse,vel.X,vel.Y);
			plvel = Vector(pl->GetVelocity());
			newpos.Z = (-/*500*/10500-plvel.Lenght()*3); //sqrt(vel.X*vel.X+vel.Y*vel.Y)*100;//*pulse;
			SetPosition(newpos);
		break;
		default:
			pos = (CtrlA+CtrlB)/2;
			pos.Z = (-/*2000*/12000-sqrt((CtrlA.X-pos.X)*(CtrlA.X-pos.X)+(CtrlA.Y-pos.Y)*(CtrlA.Y-pos.Y))*1.7f);
			oldpos = Vector(GetPosition());
//oldpos.X = 0;
//oldpos.Y = 0;
//pos.X = 0;
//pos.Y = 0;
			SetPosition(oldpos+(pos-oldpos)*.2f);
		}
	}
/*
	// Make shure we dont get lost in inacuracy
	Vector pos = GetPosition();
	Node *sun = GetNode("Sun");
	Node *len = GetNode("LensFlare");
	Node *pln = GetNode("Planet");
	Node *bac = GetNode("Background");
	Node *neb = GetNode("Nebula");
	while((pos.X> 6400*2)||(pos.X<-6400*2)||(pos.Y> 6400*2)||(pos.Y<-6400*2)){
		for(int n=0; n<MAX_PLAYERS; n++){
			char name[1024];
			sprintf(name,"Player%d",n);
			Node *a = GetNode(String(name));	// fixme: Optimize!
			if(a&&((PlayerAI*)a->GetIntelligence())){
				if(pos.X> 6400*2) a->SetPosition(0,Vector(a->GetPosition())-Vector(6400*2*2,0,0));
				if(pos.X<-6400*2) a->SetPosition(0,Vector(a->GetPosition())+Vector(6400*2*2,0,0));
				if(pos.Y> 6400*2) a->SetPosition(0,Vector(a->GetPosition())-Vector(0,6400*2*2,0));
				if(pos.Y<-6400*2) a->SetPosition(0,Vector(a->GetPosition())+Vector(0,6400*2*2,0));
			}
		}
		if(sun){
			if(pos.X> 6400*2) sun->SetPosition(0,Vector(sun->GetPosition())-Vector(6400*2*2,0,0));
			if(pos.X<-6400*2) sun->SetPosition(0,Vector(sun->GetPosition())+Vector(6400*2*2,0,0));
			if(pos.Y> 6400*2) sun->SetPosition(0,Vector(sun->GetPosition())-Vector(0,6400*2*2,0));
			if(pos.Y<-6400*2) sun->SetPosition(0,Vector(sun->GetPosition())+Vector(0,6400*2*2,0));
		}
		if(len){
			if(pos.X> 6400*2) len->SetPosition(0,Vector(len->GetPosition())-Vector(6400*2*2,0,0));
			if(pos.X<-6400*2) len->SetPosition(0,Vector(len->GetPosition())+Vector(6400*2*2,0,0));
			if(pos.Y> 6400*2) len->SetPosition(0,Vector(len->GetPosition())-Vector(0,6400*2*2,0));
			if(pos.Y<-6400*2) len->SetPosition(0,Vector(len->GetPosition())+Vector(0,6400*2*2,0));
		}
		if(pln){
			if(pos.X> 6400*2) pln->SetPosition(0,Vector(pln->GetPosition())-Vector(6400*2*2,0,0));
			if(pos.X<-6400*2) pln->SetPosition(0,Vector(pln->GetPosition())+Vector(6400*2*2,0,0));
			if(pos.Y> 6400*2) pln->SetPosition(0,Vector(pln->GetPosition())-Vector(0,6400*2*2,0));
			if(pos.Y<-6400*2) pln->SetPosition(0,Vector(pln->GetPosition())+Vector(0,6400*2*2,0));
		}
		if(bac){
			if(pos.X> 6400*2) bac->SetPosition(0,Vector(bac->GetPosition())-Vector(6400*2*2,0,0));
			if(pos.X<-6400*2) bac->SetPosition(0,Vector(bac->GetPosition())+Vector(6400*2*2,0,0));
			if(pos.Y> 6400*2) bac->SetPosition(0,Vector(bac->GetPosition())-Vector(0,6400*2*2,0));
			if(pos.Y<-6400*2) bac->SetPosition(0,Vector(bac->GetPosition())+Vector(0,6400*2*2,0));
		}
		if(neb){
			if(pos.X> 6400*2) neb->SetPosition(0,Vector(neb->GetPosition())-Vector(6400*2*2,0,0));
			if(pos.X<-6400*2) neb->SetPosition(0,Vector(neb->GetPosition())+Vector(6400*2*2,0,0));
			if(pos.Y> 6400*2) neb->SetPosition(0,Vector(neb->GetPosition())-Vector(0,6400*2*2,0));
			if(pos.Y<-6400*2) neb->SetPosition(0,Vector(neb->GetPosition())+Vector(0,6400*2*2,0));
		}
		if(pos.X> 6400*2) pos-=Vector(6400*2*2,0,0);
		if(pos.X<-6400*2) pos+=Vector(6400*2*2,0,0);
		if(pos.Y> 6400*2) pos-=Vector(0,6400*2*2,0);
		if(pos.Y<-6400*2) pos+=Vector(0,6400*2*2,0);
	}
	SetPosition(pos);
*/

	// fixme: Shouldnt wrap everything.
	Node *root = GetCreatorCamera()->GetRoot();
	Vector pos = GetPosition();
	while((pos.X> 6400*2)||(pos.X<-6400*2)||(pos.Y> 6400*2)||(pos.Y<-6400*2)){
		Node *n = root->GetNext();
		while(n){
			if(pos.X> 6400*2) n->SetPosition(0,Vector(n->GetPosition())-Vector(6400*2*2,0,0));
			if(pos.X<-6400*2) n->SetPosition(0,Vector(n->GetPosition())+Vector(6400*2*2,0,0));
			if(pos.Y> 6400*2) n->SetPosition(0,Vector(n->GetPosition())-Vector(0,6400*2*2,0));
			if(pos.Y<-6400*2) n->SetPosition(0,Vector(n->GetPosition())+Vector(0,6400*2*2,0));
			n = n->GetNext();
		}
		if(pos.X> 6400*2) pos-=Vector(6400*2*2,0,0);
		if(pos.X<-6400*2) pos+=Vector(6400*2*2,0,0);
		if(pos.Y> 6400*2) pos-=Vector(0,6400*2*2,0);
		if(pos.Y<-6400*2) pos+=Vector(0,6400*2*2,0);
	}
	SetPosition(pos);

//	GetCreatorCamera()->SetOrigin();

	OldTime=time;
	return true;
}

