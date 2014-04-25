
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include <posix/stdio.h>
//#include <Interface/Debug.h>

#include "Player.h"
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/Geometry.h>
#include <3dapi/Camera.h>
#include <3dapi/Vertex.h>
#include "RedStrobe.h"
#include "BlueStrobe.h"
#include "Boost.h"
#include "Shield.h"
#include <string.h>
#include <3dapi/IndexedPolygon.h>
//#include <stdio.h>
#include <Devices/Input/InputDevice.h>
#include "Fireball.h"
#include <Interface/View.h>
#include "Flare.h"
#include "Shock.h"
#include "Number.h"
#include <Interface/String.h>
#include "ScoreViews.h"

enum States{
	ST_EXPLODE_INIT,
	ST_EXPLODE,
	ST_PLAYING
};

#define USE_AI

//static int input_channel = 0;

static char *names[6]={
	"Textures/Ship/shipred",
	"Textures/Ship/shipyellow",
	"Textures/Ship/shipgreen",
	"Textures/Ship/shipcyan",
	"Textures/Ship/shippurple",
	"Textures/Ship/shipblue"};

//#define 

//#define PHONE_EMULATION

PlayerAI::PlayerAI(Camera *cam, Geometry *c, ScoreViews *_Scores, void *_player, int chan) : Intelligence(c), Message(){ // ,KernelClient(){
//	BoostHook=CreateHook("boost");
//	YawHook=CreateHook("yaw");
//	FireHook=CreateHook("fire");
//	RateHook=CreateHook("doublerate");
	//OrientationStep=Quaternion(Euler(0,0,0));
	//OrientationAx=Quaternion(Euler(0,0,0));

	camera = cam;
	geo = c;

//	computerplayers++;
//	view = v;

	Scores = _Scores;
	player = _player;

/*
	name = Scores->GetName(player);
	sprintf(name,"a");
*/
//	Scores->SetScore(player,0);
//	Scores->Activate(player);

//	Node *n = GetNode(String("Camera"));	// fixme: Optimize!
//	pos-=Vector(n->GetPosition());	// fixme: bug! geo is 0 sometimes
	Vector pos = Vector(camera->GetPosition())+Vector(float(rand()%0xfff)*.8f,float(rand()%0xfff)*.8f,-8000);
	pos.Z = -8000;
	SetPosition(pos);

	hook		= true; //false;
	left		= false;
	right		= false;
	wrotename	= false;
	avslutt		= false;
	addchar		= false;
	subchar		= false;
	nextchar	= false;
	number		= false;
	state		= ST_PLAYING;

	Listen("/Devices/Input/Dialogic"); //Keyboard");
	Listen("/Devices/Input/Keyboard");
	AvsluttBind = AddBind = SubBind = NextBind = HookBind = NumberBind = LeftBind = RightBind = AvsluttBind = 0;

	if(chan<100){
		char str[10];
		sprintf(str,"Player%d",chan);
		Message::SetName(str);
		#ifdef PHONE_EMULATION
		AvsluttBind = new char[strlen("C##_*")+1];
		sprintf(AvsluttBind,"C%d_#",chan);
		AddBind = new char[strlen("C##_2")+1];
		sprintf(AddBind,"C%d_2",chan);
		SubBind = new char[strlen("C##_1")+1];
		sprintf(SubBind,"C%d_1",chan);
		NextBind = new char[strlen("C##_#")+1];
		sprintf(NextBind,"C%d_*",chan);
		if(chan==0){
			HookBind = new char[strlen("##")+1];
			sprintf(HookBind,"%d",chan);
			NumberBind = new char[strlen("a")+1];
			sprintf(NumberBind,"a",chan);
			LeftBind = new char[strlen("q")+1];
			sprintf(LeftBind,"q",chan);
			RightBind = new char[strlen("w")+1];
			sprintf(RightBind,"w",chan);
		}else{
			HookBind = new char[strlen("##")+1];
			sprintf(HookBind,"%d",chan);
			NumberBind = new char[strlen("k")+1];
			sprintf(NumberBind,"k",chan);
			LeftBind = new char[strlen("i")+1];
			sprintf(LeftBind,"i",chan);
			RightBind = new char[strlen("o")+1];
			sprintf(RightBind,"o",chan);
		}
		#else
		AvsluttBind = new char[strlen("C##_*")+1];
		sprintf(AvsluttBind,"C%d_#",chan);
		AddBind = new char[strlen("C##_2")+1];
		sprintf(AddBind,"C%d_2",chan);
		SubBind = new char[strlen("C##_1")+1];
		sprintf(SubBind,"C%d_1",chan);
		NextBind = new char[strlen("C##_#")+1];
		sprintf(NextBind,"C%d_*",chan);

		HookBind = new char[strlen("C##_!Hook")+1];
		sprintf(HookBind,"C%d_!Hook",chan);
		NumberBind = new char[strlen("C##_5")+1];
		sprintf(NumberBind,"C%d_5",chan);
		LeftBind = new char[strlen("C##_4")+1];
		sprintf(LeftBind,"C%d_4",chan);
		RightBind = new char[strlen("C##_6")+1];
		sprintf(RightBind,"C%d_6",chan);
		#endif
	}else printf("Warning: Too many players! I will probably crash now.\n");

	OldTime = -1.0f;

	c->Add(Vector(-200,-200,0));
	c->Add(Vector( 200,-200,0));
	c->Add(Vector( 200, 200,0));
	c->Add(Vector(-200, 200,0));
	c->Add(Vector(-300,-300,0));
	c->Add(Vector( 300,-300,0));
	c->Add(Vector( 300, 300,0));
	c->Add(Vector(-300, 300,0));
	c->Add(Vertex(0,0,0));
	c->Add(Vertex(1,1,0));
	c->Add(Vertex(2,1,1));
	c->Add(Vertex(3,0,1));
	c->Add(Vertex(4,0,0));
	c->Add(Vertex(5,1,0));
	c->Add(Vertex(6,1,1));
	c->Add(Vertex(7,0,1));
	#ifdef USE_AI
	pol1 = new IndexedPolygon(c); //c->NewIndexedPolygon();
	pol1->Add(3);
	pol1->Add(2);
	pol1->Add(1);
	pol1->Add(0);
	#endif

	OrientationStep=Euler(0,0,0);
	OrientationAx=Euler(0,0,0);
//	Velocity=Vector(0,0,0);
	Acceleration=Vector(0,0,0);
//	OldTime=Time();
//	fire=false;
//	ShipMaterial = new Material("Textures/Ship/Ship",TEXTURE_ARGB);
	ShipMaterial = new Material(names[chan%6],Texture::cARGB);
//	ShipMaterial->SetEmissiveColor(ARGB(1,1,1));
	ShipMaterial->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	ShipMaterial->CacheAll();
	LightMaterial = new Material("Textures/Ship/ship_lightmap/lm",Texture::cARGB);
	LightMaterial->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_SOURCE);
	LightMaterial->CacheAll();
	char str[1024];
	sprintf(str,"Textures/interface/playernum/no%d",chan+1);
	NumberMaterial = new Material(str,Texture::cARGB);
	NumberMaterial->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	NumberMaterial->CacheAll();
	expm = new Material("Textures/Explosion/Explosion",Texture::cARGB);
	expm->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	expm->CacheAll();
/*
	num = new Number(this,input_channel-1);
*/
	num = 0;
	playernum = chan;

	GetCreatorGeometry()->Apply(ShipMaterial);
	LastFire = 0;
	health = 1.0f;
//	ExplotionMaterial = new Material("Textures/Explosion/Explosion");
//	state=false;
	#ifdef CHEAT
	rate = 0.1f;
	#else
	rate=.65f+float(rand())/1000000.0f;;
	#endif

	#ifdef USE_AI
	pol2 = c->NewIndexedPolygon();
	pol2->Apply(LightMaterial);
	pol2->Add(3);
	pol2->Add(2);
	pol2->Add(1);
	pol2->Add(0);
	IndexedPolygon *pol;
	#endif

//	pol = c->NewIndexedPolygon();
//	pol->Apply(NumberMaterial);
//	pol->Add(3);
//	pol->Add(2);
//	pol->Add(1);
//	pol->Add(0);

	shield=true;
	StartTime = -1.0f;
/*
	#ifdef USE_AI
	RedStrobe = new Geometry();
	RedStrobe->Node::Apply(new RedStrobeAI(RedStrobe));
	RedStrobe->SetPosition(Vector(0,0,0));
	c->Node::Apply(RedStrobe);
	BlueStrobe = new Geometry();
	BlueStrobe->Node::Apply(new BlueStrobeAI(BlueStrobe));
	BlueStrobe->SetPosition(Vector(0,0,0));
	c->Node::Apply(BlueStrobe);
	#else
	RedStrobe = 0;
	BlueStrobe = 0;
	#endif
*/
	Shield1 = new Material("Textures/Shield/Shield2",Texture::cRGB);
	Shield1->SetMode(MATERIAL_DEST_ADD_SOURCE);
	Shield1->CacheAll();
	Shield1->SetTransparency(0);
	shieldpol = new IndexedPolygon(c);
	shieldpol->Apply(Shield1);
	shieldpol->Add(7);
	shieldpol->Add(6);
	shieldpol->Add(5);
	shieldpol->Add(4);

	RedStrobe  = new Material("Textures/Ship/RStrobe",Texture::cRGB);
	RedStrobe->SetMode(MATERIAL_DEST_ADD_SOURCE);
	RedStrobe->CacheAll();
	redpol = new IndexedPolygon(c);
	redpol->Apply(RedStrobe);
	redpol->Add(3);
	redpol->Add(2);
	redpol->Add(1);
	redpol->Add(0);
	BlueStrobe  = new Material("Textures/Ship/BStrobe",Texture::cRGB);
	BlueStrobe->SetMode(MATERIAL_DEST_ADD_SOURCE);
	BlueStrobe->CacheAll();
	bluepol = new IndexedPolygon(c);
	bluepol->Apply(BlueStrobe);
	bluepol->Add(3);
	bluepol->Add(2);
	bluepol->Add(1);
	bluepol->Add(0);

	Boost = new Material("Textures/Boost/Flame",Texture::cRGB);
	Boost->SetMode(MATERIAL_DEST_ADD_SOURCE|MATERIAL_SOURCE_DIFFUSE);
	Boost->CacheAll();
	#ifdef DOUBLE_BOOST
	c->Add(Vector(-5*4-50, 20*4+200,0));
	c->Add(Vector( 5*4-50, 20*4+200,0));
	c->Add(Vector( 5*4-50,-20*4+200,0));
	c->Add(Vector(-5*4-50,-20*4+200,0));
	c->Add(Vector(-5*4+50, 20*4+200,0));
	c->Add(Vector( 5*4+50, 20*4+200,0));
	c->Add(Vector( 5*4+50,-20*4+200,0));
	c->Add(Vector(-5*4+50,-20*4+200,0));
	c->Add(Vertex( 4+4,0,0));
	c->Add(Vertex( 5+4,0,1));
	c->Add(Vertex( 6+4,1,1));
	c->Add(Vertex( 7+4,1,0));
	c->Add(Vertex( 8+4,0,0));
	c->Add(Vertex( 9+4,0,1));
	c->Add(Vertex(10+4,1,1));
	c->Add(Vertex(11+4,1,0));
	BoostPoly1 = new IndexedPolygon(c);
	BoostPoly1->Apply(Boost);
	BoostPoly1->Add(4+4); BoostPoly1->Add(5+4); BoostPoly1->Add(6+4); BoostPoly1->Add(7+4);
	BoostPoly2 = new IndexedPolygon(c);
	BoostPoly2->Apply(Boost);
	BoostPoly2->Add(8+4); BoostPoly2->Add(9+4); BoostPoly2->Add(10+4); BoostPoly2->Add(11+4);
	#else
	c->Add(Vector(-12*4, 20*4+200,0));
	c->Add(Vector( 12*4, 20*4+200,0));
	c->Add(Vector( 12*4,-20*4+200,0));
	c->Add(Vector(-12*4,-20*4+200,0));
	c->Add(Vertex( 4+4,0,1));
	c->Add(Vertex( 5+4,1,1));
	c->Add(Vertex( 6+4,1,0));
	c->Add(Vertex( 7+4,0,0));
	BoostPoly1 = new IndexedPolygon(c);
	BoostPoly1->Apply(Boost);
	BoostPoly1->Add(4+4); BoostPoly1->Add(5+4); BoostPoly1->Add(6+4); BoostPoly1->Add(7+4);
	#endif

//	LeftBoost = new Geometry();
//	LeftBoost->Node::Apply(new BoostAI(LeftBoost,c));
//	LeftBoost->SetPosition(Vector(50,200,0));
//	c->Node::Apply(LeftBoost);
//	RightBoost = new Geometry();
//	RightBoost->Node::Apply(new BoostAI(RightBoost,c));
//	RightBoost->SetPosition(Vector(-50,200,0));
//	c->Node::Apply(RightBoost);
/*
	Shield = new Geometry();
	shieldAI = new ShieldAI(Shield);
	Shield->Node::Apply(0,shieldAI);
	Shield->SetPosition(0,Vector(0,30,0));
	c->Node::Apply(0,Shield);
*/
//	shieldAI = new ShieldAI(geo);

//	Sound = new SoundPoint("Sound/Quake/Enforcer/Enfire.wav");
//	Sound->SetPosition(Vector(0,0,0));

//	Velocity		= Vector(0,0,0);
	Acceleration	= Vector(0,0,0);
	OrientationStep	= Euler(0,0,0);
	OrientationAx	= Euler(0,0,0);
//	SetPosition(Vector(0,0,-800000));

#if 0
	#ifdef USE_AI
	AddSensor(Vector(0,-300000,0));
	// Left
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,.05f*1.0f*1.0f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,.10f*1.1f*1.1f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,.15f*1.2f*1.2f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,.20f*1.3f*1.3f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,.25f*1.4f*1.4f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,.30f*1.5f*1.5f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,.35f*1.6f*1.6f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,.40f*1.7f*1.7f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,.45f*1.8f*1.8f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,.50f*1.9f*1.9f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,.55f*2.0f*2.0f)));
	// Right
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,-.05f*1.0f*1.0f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,-.10f*1.1f*1.1f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,-.15f*1.2f*1.2f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,-.20f*1.3f*1.3f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,-.25f*1.4f*1.4f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,-.30f*1.5f*1.5f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,-.35f*1.6f*1.6f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,-.40f*1.7f*1.7f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,-.45f*1.8f*1.8f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,-.50f*1.9f*1.9f)));
	AddSensor(Vector(0,-300000,0)*Quaternion(Euler(0,0,-.55f*2.0f*2.0f)));
	#endif
#endif

	score = 0;
//	char str[1024];
//	sprintf(str,"%d",score);
//	view->ConsoleStream::Clear();
//	view->Print("0");
//	AddScore(0);
	bounce = false;

	Acceleration = Vector(0,0.1f,0);

	activate_shield = false;
	charge = 10.0f;

	OldVelocity = Vector(0,0,0);

	redpulse  = 0.2f+float(rand())/100000.0f;
	bluepulse = 0.2f+float(rand())/100000.0f;
	shield_active = true;
}
PlayerAI::~PlayerAI(){
	//delete FireballGeo;
	delete ShipMaterial;
//	delete ExplotionMaterial;
	delete LightMaterial;
	delete NumberMaterial;
	delete expm;
//	if(RedStrobe) RedStrobe->Kill();
//	if(BlueStrobe) BlueStrobe->Kill();
	delete RedStrobe;
	delete BlueStrobe;
	delete Boost;
	delete Shield1;
//	if(LeftBoost) LeftBoost->Kill();
//	if(RightBoost) RightBoost->Kill();
////	if(Shield) Shield->Kill();
//	if(Shield) Shield->Kill(0);
//	computerplayers--;
	if(AddBind)		delete AddBind;
	if(SubBind)		delete SubBind;
	if(NextBind)	delete NextBind;
	if(HookBind)	delete HookBind;
	if(NumberBind)	delete NumberBind;
	if(AvsluttBind)	delete AvsluttBind;
	if(LeftBind)	delete LeftBind;
	if(RightBind)	delete RightBind;
}

void PlayerAI::Spawn(void){
	Vector pos = Vector(camera->GetPosition())+Vector(float(rand()%0xfff)*.8f,float(rand()%0xfff)*.8f,-8000);
	pos.Z = -8000;
	SetPosition(pos);

	score			= 0;
	bounce			= false;
	activate_shield	= true;
	ShieldStart		= -1;
	charge			= 10.0f;
	shield			= false;
	if(state!=ST_PLAYING){
		pol2 = new IndexedPolygon(geo);
		pol2->Apply(LightMaterial);
		pol2->Add(3);
		pol2->Add(2);
		pol2->Add(1);
		pol2->Add(0);
		pol1->Apply(ShipMaterial);
		BoostPoly1 = new IndexedPolygon(geo);
		BoostPoly1->Apply(Boost);
		BoostPoly1->Add(4+4); BoostPoly1->Add(5+4); BoostPoly1->Add(6+4); BoostPoly1->Add(7+4);
		#ifdef DOUBLE_BOOST
		BoostPoly2 = new IndexedPolygon(geo);
		BoostPoly2->Apply(Boost);
		BoostPoly2->Add(8+4); BoostPoly2->Add(9+4); BoostPoly2->Add(10+4); BoostPoly2->Add(11+4);
		#endif
		redpol = new IndexedPolygon(geo);
		redpol->Apply(BlueStrobe);
		redpol->Add(3); redpol->Add(2); redpol->Add(1); redpol->Add(0);
		bluepol = new IndexedPolygon(geo);
		bluepol->Apply(BlueStrobe);
		bluepol->Add(3); bluepol->Add(2); bluepol->Add(1); bluepol->Add(0);
		shieldpol = new IndexedPolygon(geo);
		shieldpol->Apply(Shield1);
		shieldpol->Add(7);
		shieldpol->Add(6);
		shieldpol->Add(5);
		shieldpol->Add(4);
	}
	state			= ST_PLAYING;

	OrientationStep	= Euler(0,0,0);
	OrientationAx	= Euler(0,0,0);
	Acceleration	= Vector(0,0.1f,0);
	OldVelocity		= Vector(0,0,0);

//Vector c = Vector(camera->GetPosition());
//Vector p = Vector(GetPosition());
//printf("!!!!!!!!!!! (%f,%f,%f),(%f,%f,%f)\n",c.X,c.Y,c.Z,p.X,p.Y,p.Z);

	StartTime = -1;
	ShieldStart = -1;
	shield_active = true;
}

bool PlayerAI::Tick(double time){
//Vector p = Vector(GetPosition());
//printf("Player (%f,%f,%f)\n",p.X,p.Y,p.Z);


	switch(state){
	case ST_EXPLODE_INIT:
//printf("ST_EXPLODE_INIT\n");
		ExplodeTime = time;
//		((RedStrobeAI*)(RedStrobe->GetIntelligence()))->Deactivate();
//		((BlueStrobeAI*)(BlueStrobe->GetIntelligence()))->Deactivate();
//		((BoostAI*)(LeftBoost->GetIntelligence()))->Deactivate();
//		((BoostAI*)(RightBoost->GetIntelligence()))->Deactivate();
//		((ShieldAI*)(Shield->GetIntelligence()))->Deactivate();
		pol1->Apply(expm);
		if(pol2) delete pol2;
		if(BoostPoly1) delete BoostPoly1;
		#ifdef DOUBLE_BOOST
		if(BoostPoly2) delete BoostPoly2;
		#endif
		if(redpol) delete redpol;
		if(bluepol) delete bluepol;
		if(shieldpol) delete shieldpol;
		pol2 = 0;
		BoostPoly1 = 0;
		BoostPoly2 = 0;
		redpol = 0;
		bluepol = 0;
		shieldpol = 0;
		state = ST_EXPLODE;
		ShieldStart = time-8.0f;
	break;
	case ST_EXPLODE:{
//printf("ST_EXPLODE\n");
		if(time-ExplodeTime<1){
			// Animate explotion
//			SetPosition(Vector(GetPosition())+Velocity*pulse);
			int framecount = expm->GetTexture()->GetFrameCount();
			if(framecount)   expm->GetTexture()->SetFrame(int((time-ExplodeTime)*framecount/1.0f)%framecount);
		}else if(time-ExplodeTime<3){
			// Delay
//			SetPosition(Vector(GetPosition())+Velocity*pulse);
			expm->GetTexture()->SetFrame(0);
		}else{
			// Respawn

	Vector pos = Vector(camera->GetPosition())+Vector(float(rand()%0xfff)*.8f,float(rand()%0xfff)*.8f,-8000);
	pos.Z = -8000;
	SetPosition(pos);

//	Node *n = GetNode(String("Camera"));	// fixme: Optimize!
//	SetPosition(Vector(n->GetPosition())+Vector(float(rand()%0xfff)*.8f,float(rand()%0xfff)*.8f,-8000));
//			((RedStrobeAI*)(RedStrobe->GetIntelligence()))->Activate();
//			((BlueStrobeAI*)(BlueStrobe->GetIntelligence()))->Activate();
//			((BoostAI*)(LeftBoost->GetIntelligence()))->Activate();
//			((BoostAI*)(RightBoost->GetIntelligence()))->Activate();
//			((ShieldAI*)(Shield->GetIntelligence()))->Activate();
			state = ST_PLAYING;
			pol2 = new IndexedPolygon(geo);
			pol2->Apply(LightMaterial);
			pol2->Add(3);
			pol2->Add(2);
			pol2->Add(1);
			pol2->Add(0);
			pol1->Apply(ShipMaterial);
			BoostPoly1 = new IndexedPolygon(geo);
			BoostPoly1->Apply(Boost);
			BoostPoly1->Add(4+4); BoostPoly1->Add(5+4); BoostPoly1->Add(6+4); BoostPoly1->Add(7+4);
			#ifdef DUBLE_BOOST
			BoostPoly2 = new IndexedPolygon(geo);
			BoostPoly2->Apply(Boost);
			BoostPoly2->Add(8+4); BoostPoly2->Add(9+4); BoostPoly2->Add(10+4); BoostPoly2->Add(11+4);
			#endif
			redpol = new IndexedPolygon(geo);
			redpol->Apply(BlueStrobe);
			redpol->Add(3); redpol->Add(2); redpol->Add(1); redpol->Add(0);
			bluepol = new IndexedPolygon(geo);
			bluepol->Apply(BlueStrobe);
			bluepol->Add(3); bluepol->Add(2); bluepol->Add(1); bluepol->Add(0);
			shieldpol = new IndexedPolygon(geo);
			shieldpol->Apply(Shield1);
			shieldpol->Add(7); shieldpol->Add(6); shieldpol->Add(5); shieldpol->Add(4);
			Shield1->SetTransparency(0);
			activate_shield = false;
			shield = true;
			ShieldStart = time-6.0f;
		}
	}break;
	case ST_PLAYING:
//printf("ST_PLAYING\n");

		int framecount = RedStrobe->GetTexture()->GetFrameCount();
		int frame = int(time*framecount/redpulse)%(framecount*4);
		if(frame>=framecount) frame=0;
		if(framecount) RedStrobe->GetTexture()->SetFrame(frame);

		framecount = BlueStrobe->GetTexture()->GetFrameCount();
		frame = int(time*framecount/bluepulse)%(framecount*4);
		if(frame>=framecount) frame=0;
		if(framecount) BlueStrobe->GetTexture()->SetFrame(frame);




		framecount = Boost->GetTexture()->GetFrameCount();
		frame = rand()%(framecount-1);
		if(framecount) Boost->GetTexture()->SetFrame(frame);

		Vector vel = Vector(GetVelocity());
		vel-=OldVelocity;
		float val = vel.Lenght()*5.0f;
		OldVelocity = Vector(GetVelocity());
		if(val<500){
			#ifdef DOUBLE_BOOST
			SetVector(0+4+4,Vector(-5*4-50, val-20+200,0));
			SetVector(1+4+4,Vector( 5*4-50, val-20+200,0));
			SetVector(0+8+4,Vector(-5*4+50, val-20+200,0));
			SetVector(1+8+4,Vector( 5*4+50, val-20+200,0));
			#else
			SetVector(0+4+4,Vector(-12*4, val+50+200,0));
			SetVector(1+4+4,Vector( 12*4, val+50+200,0));
			#endif
		}




//		if(activate_shield) shieldAI->Activate();
		if(activate_shield){
			ShieldStart = time;
			if(!shieldpol){
				shieldpol = new IndexedPolygon(geo);
				shieldpol->Apply(Shield1);
				shieldpol->Add(7);
				shieldpol->Add(6);
				shieldpol->Add(5);
				shieldpol->Add(4);
			}
		}
		activate_shield = false;

		if(time-ShieldStart<8.0f){
			float t = time-ShieldStart-7.0f;
			Shield1->SetTransparency(t>0?t:0);
			shield_active = true;
		}else{
			Shield1->SetTransparency(1);
			shield_active = false;
		}

/*
		if(bounce){
	//		new Shock(this,BounceDirection*-Quaternion(GetOrientation()));
			SetVelocity(-Vector(GetVelocity()));
			bounce = false;
		}
*/

		if(StartTime<0.0f) OldTime = StartTime = time;
		if((time-StartTime)>5.0f) shield=false;
		pulse=float(time-OldTime);
//		if(pulse>0){

			charge += pulse;
			if(charge>=10.0f) charge = 10.0f;

	#if 1
		// AI stuff

//			if(hook){
				if(!num) num = new Number(camera,this,playernum);
	/*
	//printf("%d\n",hook);
				//#ifndef PHONE_EMULATION
				if(!wrotename){
					//score = 0;
					//AddScore(0);
					if(avslutt){
						name[strlen(name)-1]='\0';
						if(!strcmp(name,"")) sprintf(name,"ano");
						wrotename = true;
						AddScore(0);
						//Scores->Activate(player);
					}
					#ifdef NORSK
					if(charsub){
						name[strlen(name)-1]--;
						if(name[strlen(name)-1])=='a'-1) name[strlen(name)-1] = 'å';
						if(name[strlen(name)-1])=='å'-1) name[strlen(name)-1] = 'ø';
						if(name[strlen(name)-1])=='ø'-1) name[strlen(name)-1] = 'æ';
						if(name[strlen(name)-1])=='æ'-1) name[strlen(name)-1] = 'z';
					}
					if(charadd){
						name[strlen(name)-1]++;
						if(name[strlen(name)-1])=='z'+1) name[strlen(name)-1] = 'æ';
						if(name[strlen(name)-1])=='æ'+1) name[strlen(name)-1] = 'ø';
						if(name[strlen(name)-1])=='ø'+1) name[strlen(name)-1] = 'å';
						if(name[strlen(name)-1])=='å'+1) name[strlen(name)-1] = 'a';
					}
					#elif defined(SVENSK)
					if(charsub){
						name[strlen(name)-1]--;
						if(name[strlen(name)-1])=='a'-1) name[strlen(name)-1] = 'å';
						if(name[strlen(name)-1])=='å'-1) name[strlen(name)-1] = 'ö';
						if(name[strlen(name)-1])=='ö'-1) name[strlen(name)-1] = 'ä';
						if(name[strlen(name)-1])=='ä'-1) name[strlen(name)-1] = 'z';
					}
					if(charadd){
						name[strlen(name)-1]++;
						if(name[strlen(name)-1])=='z'+1) name[strlen(name)-1] = 'ä';
						if(name[strlen(name)-1])=='ä'+1) name[strlen(name)-1] = 'ö';
						if(name[strlen(name)-1])=='ö'+1) name[strlen(name)-1] = 'å';
						if(name[strlen(name)-1])=='å'+1) name[strlen(name)-1] = 'a';
					}
					#else
					if(subchar) name[strlen(name)-1]--;
					if(addchar) name[strlen(name)-1]++;
					name[strlen(name)-1] = ((name[strlen(name)-1]-'a')%('z'-'a'))+'a';
					#endif
					if(nextchar) sprintf(name,"%s%c",name,name[strlen(name)-1]);
					addchar = subchar = nextchar = 0;
					AddScore(0);
					if(strlen(name)==4){
						wrotename = true;
						name[3]='\0';
						//Scores->Activate(player);
					}
				}else{
	*/
//printf("%d,%d\n",left,right);
					if(left) OrientationAx=Euler(0,0,1.0f);
					else if(right) OrientationAx=Euler(0,0,-1.0f);
					else OrientationAx=Euler(0,0,0);
	/*
					if(number){
						NumberMaterial->SetTranslusency(1);
					}else{
						NumberMaterial->SetTranslusency(0);
					}
	*/

					if(number) num->Activate();
					//else num->Activate(false);

	//			}
			/*}else{

				wrotename = false;
				if((score!=0)||strcmp(name,"a")){
					score = 0;
					sprintf(name,"a");
					AddScore(0);
				}
	#ifdef USE_AI
				// Find safe directions
				Vector mypos = Vector(GetPosition());
				float ul=0,ur=0,ll=0,lr=0;
				Node *node = GetFirstNode();
				while(node){
					Vector pos = Vector(node->GetPosition())-mypos;
					float dist = pos.SquareLenght();
					if(pos.X<0){
						if(pos.Y<0) ul+=1.0f/dist;
						else ll+=1.0f/dist;
					}else{
						if(pos.Y<0) ur+=1.0f/dist;
						else lr+=1.0f/dist;
					}
					node = node->GetNext(node);
				}

				if(Velocity.X<0){
					if(Velocity.Y<0){
						// ul
						
						if(ur<ul){
							OrientationAx=Euler(0,0,1.0f);
						}else if(ll<ul){
							OrientationAx=Euler(0,0,-1.0f);
						}else{
							OrientationAx=Euler(0,0,0);
						}
						
						if(ur<ul){
							if(ll<ur){
								if(lr<ll){
								}else{
								}
							}else{
								if(lr<ur){
								}else{
								}
							}
						}else{
							if(ll<ul){
								if(lr<ul){
								}else{
								}
							}else{
								if(lr<ul){
								}else{
								}
							}
						}
					}else{
						// ll
						if(ul<ll){
							OrientationAx=Euler(0,0,-1.0f);
						}else if(lr<ll){
							OrientationAx=Euler(0,0,1.0f);
						}else{
							OrientationAx=Euler(0,0,0);
						}
					}
				}else{
					if(Velocity.Y<0){
						// ur
						if(ul<ur){
							OrientationAx=Euler(0,0,-1.0f);
						}else if(lr<ur){
							OrientationAx=Euler(0,0,1.0f);
						}else{
							OrientationAx=Euler(0,0,0);
						}
					}else{
						// lr
						if(ur<lr){
							OrientationAx=Euler(0,0,1.0f);
						}else if(ll<lr){
							OrientationAx=Euler(0,0,-1.0f);
						}else{
							OrientationAx=Euler(0,0,0);
						}
					}
				}
				//	OrientationAx=Euler(0,0,1.0f); //Quaternion(Euler(0,0,-Yaw));
	#endif
	//			Acceleration = Vector(0,0.1f,0);
			}*/
	#endif


/*			if(state){
				SetPosition(Vector(GetPosition())+Velocity*pulse);
				int framecount = GetCreatorGeometry()->GetMaterial()->GetTexture()->GetFrameCount();
				if(framecount) GetCreatorGeometry()->GetMaterial()->GetTexture()->SetFrame(int((time-ExpTime)*framecount/0.5f)%framecount);
			#ifndef CHEAT
	#if 0
			}else if(health<=0.0f){
				state=true;
				RedStrobe->Kill();
				BlueStrobe->Kill();
				LeftBoost->Kill();
				RightBoost->Kill();
				RedStrobe=0;
				BlueStrobe=0;
				LeftBoost=0;
				RightBoost=0;
				GetCreatorGeometry()->Apply(ExplotionMaterial);
				ExpTime = time;
				OldTime = time;
				return true;
	#endif
			#endif
			}else{
*/
	#define	MaxVel	20000.0f
	#define RotScalar	5.0f
				// Acelerate rotation
				//OrientationStep=(OrientationAx*pulse*RotScalar)*OrientationStep;	// Rotation per sec
				OrientationStep+=(OrientationAx*pulse*RotScalar);
				// Acelerate velocity
				SetVelocity(Vector(GetVelocity())-(Acceleration*pulse*MaxVel)*Quaternion(GetOrientation()));								// Translation per sec
				// Dampening
				// fixme: This dampening shit doesnt work right
				//Quaternion RDamp=OrientationStep*-5.0f;
				//OrientationStep=OrientationStep*(RDamp*pulse);
				Euler RDamp = OrientationStep*-2.0f;
				OrientationStep+=RDamp*pulse;
				Vector VDamp=Vector(GetVelocity())*-1.0f;
				SetVelocity(Vector(GetVelocity())+VDamp*pulse);

				//SetOrientation((OrientationStep*pulse)*Quaternion(GetOrientation()));
				Orientation+=OrientationStep*pulse;
				SetOrientation(Quaternion(Orientation));
//				SetPosition(Vector(GetPosition())+Velocity*pulse);
//			}
//			if(state){
//				OldTime = time;
//				return true;
//		}

	//		int framecount = GetCreatorGeometry()->GetMaterial()->GetTexture()->GetFrameCount();
	if(Orientation.Roll>(3.14f*2)) Orientation.Roll-=3.14f*2;
	if(Orientation.Roll<0) Orientation.Roll+=3.14f*2;
	//		int frame = abs((int)((Orientation.Roll/(3.14f*2))*-framecount));
	//printf("%d\n",frame);
	//		if(framecount) GetCreatorGeometry()->GetMaterial()->GetTexture()->SetFrame(frame%framecount);

			framecount = LightMaterial->GetTexture()->GetFrameCount();
			frame = abs(int((Orientation.Roll/(3.14f*2))*-framecount));
			if(framecount) LightMaterial->GetTexture()->SetFrame(frame%framecount);

	//#ifdef USE_AI
	#if 1
//			if(hook){
				if((time-LastFire)>rate){ //1.0f){
					LastFire=time;
					Geometry *geo = new Geometry();
					geo->Node::Apply(0,new Flare(geo,this,player,Scores));
					Node *n = GetParent();
					n->Apply(0,geo);
				}
//			}
	#endif
	//#endif

	//#if 0
			//Node *n = GetNode("Camera");
			//if(n){
				Vector cpos = Vector(camera->GetPosition());
				Vector pos = Vector(GetPosition());
cpos.Z+=10000;
				float orgZ = pos.Z;
				Vector dist = pos-cpos;
dist.Z = 0;
				if(dist.SquareLenght()>6000.0f*6000.0f){
					//printf("%f\n",10000.0f/dist.Lenght());
					pos-=dist*(1.0f-(6000.0f/dist.Lenght()));
					pos.Z=orgZ;
					SetPosition(pos);
				}
			//}

		//}
	break;
	}
//#endif
	OldTime=time;
//lastpulse=pulse;
	return true;
}

void PlayerAI::MessageReceived(double time, int Cmd, void *args){
	// fixme: Use time!
	static float Yaw=0,Boost=0;
//	if(Cmd==BoostHook){
//		PositionAx=Vector((Vector*)args);
//	}else if(Cmd==YawHook){
//		Yaw=((float*)args)[0];
//		OrientationAx=Euler(0,0,Yaw); //Quaternion(Euler(0,0,-Yaw));
//	}else if(Cmd==FireHook){
////fire=true;
		// fixme: This shit must be thread protected!
		//Geometry *Fireball = new Geometry(FireballGeo);
		//     if(GetParentCamera())		GetParentCamera()->Apply(Fireball);		// Fireball removes it self
		//else if(GetParentGeometry())	GetParentGeometry()->Apply(Fireball);	// Fireball removes it self
		//else if(GetParentLightPoint())	GetParentLightPoint()->Apply(Fireball);	// Fireball removes it self
		//Fireball->Apply(new FireballAI(Fireball));
//	}else if(Cmd==RateHook){
//		rate/=2.0f;
//	}
}

//Vector *PlayerAI::GetVelocity(void){
//	return &Velocity;
//}

static String RockName		= String("Rock");
static String Player1Name	= String("Player0");
static String Player2Name	= String("Player1");
static String Player3Name	= String("Player2");
static String Player4Name	= String("Player3");
static String Player5Name	= String("Player4");
static String Player6Name	= String("Player5");
static String Player7Name	= String("Player6");
static String Player8Name	= String("Player7");
static String Player9Name	= String("Player8");
static String Player10Name	= String("Player9");
static String Player11Name	= String("Player10");
static String Player12Name	= String("Player11");
static String Player13Name	= String("Player12");
static String Player14Name	= String("Player13");
static String Player15Name	= String("Player14");
static String Player16Name	= String("Player15");
static String Player17Name	= String("Player16");
static String Player18Name	= String("Player17");
static String Player19Name	= String("Player18");
static String Player20Name	= String("Player19");
static String Player21Name	= String("Player20");
static String Player22Name	= String("Player21");
static String Player23Name	= String("Player22");
static String Player24Name	= String("Player23");
static String Player25Name	= String("Player24");
static String Player26Name	= String("Player25");
static String Player27Name	= String("Player26");
static String Player28Name	= String("Player27");
static String Player29Name	= String("Player28");
static String Player30Name	= String("Player29");

bool PlayerAI::BoundingSphereIntersection(float sqrdist, class Node *caller){
//return false;
//printf("%s\n",caller->GetName().GetString());

	switch(state){
	case ST_PLAYING:
		bool collided = false;
//		if(!state){
			bool field = true;
//printf("%s\n",caller->GetName());
			/*if(caller->GetName()==RockName){ //String("Rock")){		// fixme: Optimize!
				sqrdist+=400;
				if(sqrdist<0){
					//if((lasthit-time)>1.0f){
					charge-=1;
					if(charge<0){
//						AddScore(-100);
						//explode = true;
					}else{
//						AddScore(-50);
					}
				}
			}else*/ if(caller->GetName()==RockName){ //String("Rock")){		// fixme: Optimize!
				sqrdist+=400;
				if(sqrdist<0){
					charge-=1;
					collided = true;
					//PositionStep=-PositionStep;
//					SetPosition(Vector(GetPosition())-Velocity*pulse);
					if(!shield) health-=0.1f/2.0f;
	//				SendMessage(GetHook("sethealth"),&health);
	//				shieldAI->Collide(OldTime);
//					score-=50;
					//char str[1024];
					//sprintf(str,"%d",score);
					//view->ConsoleStream::Clear();
					//view->Print(str);
					if(Scores) Scores->SetScore(player,score);
				}
			}/*else if(caller->GetName()==String("Rock_sub")){	// fimxe: Optimize!
				sqrdist+=20000;
				if(sqrdist<0){
					collided = true;
					//PositionStep=-PositionStep;
					SetPosition(Vector(GetPosition())-(PositionStep*pulse));
					if(!shield) health-=0.09f/2.0f;
	//				SendMessage(GetHook("sethealth"),&health);
					shieldAI->Collide(OldTime);
	//				score-=25.0f;
	//				char str[1024];
	//				sprintf(str,"%d",score);
	//				view->ConsoleStream::Clear();
	//				view->Print(str);
				}
			}else if(caller->GetName()==String("Rock_sub_sub")){	// fixme: Optimize!
				sqrdist+=10000;
				if(sqrdist<0){
					collided = true;
					//PositionStep=-PositionStep;
					SetPosition(Vector(GetPosition())-(PositionStep*pulse));
					if(!shield) health-=0.08f/2.0f;
	//				SendMessage(GetHook("sethealth"),&health);
					shieldAI->Collide(OldTime);
	//				score-=10.0f;
	//				char str[1024];
	//				sprintf(str,"%d",score);
	//				view->ConsoleStream::Clear();
	//				view->Print(str);
				}
			}*/else if(
					 caller->GetName()==Player1Name|| //String("Player1")||		// fixme: Optimize!
					 caller->GetName()==Player2Name||
					 caller->GetName()==Player3Name||
					 caller->GetName()==Player4Name||
					 caller->GetName()==Player5Name||
					 caller->GetName()==Player6Name||
					 caller->GetName()==Player7Name||
					 caller->GetName()==Player8Name||
					 caller->GetName()==Player9Name||
					 caller->GetName()==Player10Name||
					 caller->GetName()==Player11Name||
					 caller->GetName()==Player12Name||
					 caller->GetName()==Player13Name||
					 caller->GetName()==Player14Name||
					 caller->GetName()==Player15Name||
					 caller->GetName()==Player16Name||
					 caller->GetName()==Player17Name||
					 caller->GetName()==Player18Name||
					 caller->GetName()==Player19Name||
					 caller->GetName()==Player20Name||
					 caller->GetName()==Player21Name||
					 caller->GetName()==Player22Name||
					 caller->GetName()==Player23Name||
					 caller->GetName()==Player24Name||
					 caller->GetName()==Player25Name||
					 caller->GetName()==Player26Name||
					 caller->GetName()==Player27Name||
					 caller->GetName()==Player28Name||
					 caller->GetName()==Player29Name||
					 caller->GetName()==Player30Name){
				sqrdist+=100;

				PlayerAI *pl = (PlayerAI*)caller->GetIntelligence();
				if(pl->IsAlive()){
					if(sqrdist<0){
						charge-=1;
						//PositionStep=-PositionStep;
						collided = true;
	//					SetPosition(Vector(GetPosition())-Velocity*pulse);
						if(!shield) health-=0.08f/2.0f;
		//				SendMessage(GetHook("sethealth"),&health);
				//		shieldAI->Collide(OldTime);
		//				score-=25.0f;
		//				char str[1024];
		//				sprintf(str,"%d",score);
		//				view->ConsoleStream::Clear();
		//				view->Print(str);
					}
				}

			}else if(caller->GetName()==String("FirePickup")){	// fixme: Optimize!
				caller->Kill(0);
				activate_shield = true;
			}else{
				field = false;
			}
			//if(shield) new Field();
			
			if(collided){
	//pulse+=.001f;
	//PositionStep+=Vector(0.001f,0,0);
				Vector pos = Vector(GetPosition())-Vector(caller->GetPosition());
//printf("%f\n",sqrt(-sqrdist));
//printf("%f,%f,%f\n",pos.X,pos.Y,pos.Z);
				pos/=pos.Lenght();
//printf("%f,%f,%f\n",pos.X,pos.Y,pos.Z);
				pos*=sqrt(-sqrdist);
//printf("%f,%f,%f\n",pos.X,pos.Y,pos.Z);
//				SetPosition(Vector(GetPosition())+pos);
				SetVelocity(Vector(GetVelocity())+pos*-Quaternion(GetOrientation()));

				//float mult = sqrt(sqrt(geo->GetSquareRadius()+caller->GetSquareRadius())/pos.Lenght());
				//SetPosition(Vector(GetPosition())+pos*mult);

				//printf("%f,%f,%f\n",pos.X,pos.Y,pos.Z);
				//SetPosition(Vector(GetPosition())+pos);
				//bounce = true;
				//BounceDirection = pos;
				return true;
			}
		//}
	break;
	}
	return false;
}

void PlayerAI::MessageReceived(void){
//printf("PlayerAI::MessageReceived()\n");
	int cnt = GetReceivedCount();
	//printf("Commands %d\n",cnt);
	char *buf = (char*)GetReceivedBuffer();
	for(int n=0; n<cnt; n++){
		switch(GetReceivedCommand(n)){
		case INPUT_DIGITAL_DOWN:{
			//printf("Key down\n");
			int len = *(int16*)buf;
			buf+=sizeof(int16);
			char *str = new char[len+1];
			for(int n=0; n<len; n++){
				str[n]=*buf++;
			}
			str[len]='\0';
//printf("%s down (%s)\n",str,NextBind);
//			if(AddBind)    if(!strcmp(str,AddBind))		 addchar = true;
//			if(SubBind)    if(!strcmp(str,SubBind))		 subchar = true;
//			if(NextBind)    if(!strcmp(str,NextBind))    nextchar = true;
//			if(HookBind)    if(!strcmp(str,HookBind)){
//				hook = true;
//				Scores->Activate(player);
//			}
			if(NumberBind)  if(!strcmp(str,NumberBind))  number = true;
//			if(AvsluttBind) if(!strcmp(str,AvsluttBind)) avslutt = true;
			if(LeftBind)    if(!strcmp(str,LeftBind))    left = true;
			if(RightBind)   if(!strcmp(str,RightBind))   right = true;
			delete str;
		}break;
		case INPUT_DIGITAL_UP:{
			//printf("Key up\n");
			int len = *(int16*)buf;
			buf+=sizeof(int16);
			char *str = new char[len+1];
			for(int n=0; n<len; n++){
				str[n]=*buf++;
			}
			str[len]='\0';
//printf("%s up (%s)\n",str,NextBind);
//			if(AddBind)		if(!strcmp(str,AddBind))	 addchar = false;
//			if(SubBind)		if(!strcmp(str,SubBind))	 subchar = false;
//			if(NextBind)	if(!strcmp(str,NextBind))    nextchar = false;
//			if(HookBind)    if(!strcmp(str,HookBind)){
//				hook = false;
//				Scores->Deactivate(player);
//				Kill();
//			}
			if(NumberBind)  if(!strcmp(str,NumberBind))  number = false;
//			if(AvsluttBind) if(!strcmp(str,AvsluttBind)) avslutt = false;
			if(LeftBind)    if(!strcmp(str,LeftBind))    left = false;
			if(RightBind)   if(!strcmp(str,RightBind))   right = false;
			delete str;
		}break;
		case ADD_SCORE:
			//printf("ADD_SCORE\n");
			int32 val;
			Get(val);
//printf("%d\n",val);
			AddScore(val);
		break;
		}
	}
}


void PlayerAI::AddScore(int add){
	score+=add;
//	char str[1024];
//	sprintf(str,"%d %s",score,name);
//	view->ConsoleStream::Clear();
//	view->Print(str);
	if(Scores) Scores->SetScore(player,score);
}

void PlayerAI::Explode(void){
	//explode = true;
//	if(!shieldAI->Active()) state = ST_EXPLODE_INIT;
	if(!shield_active) state = ST_EXPLODE_INIT;
}

bool PlayerAI::IsAlive(void){
	return state==ST_PLAYING;
}

