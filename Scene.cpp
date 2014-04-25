
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdio.h>
#include <posix/stdlib.h>
#include <posix/string.h>
#include "Scene.h"
#include <3dapi/Geometry.h>
#include "Background.h"
#include "Nebula.h"
#include "Planet.h"
#include "Sun.h"
#include "LensFlare.h"
#include <3dapi/Camera.h>
#include "CameraAI.h"
#include <Interface/View.h>
#include "Player.h"
#include "ScoreViews.h"
#include <3dapi/IndexedPolygon.h>
#include "RockAI.h"
#include <Interface/DynamicArray.h>
#include <Devices/Input/InputDevice.h>
#include <3dapi/Material.h>
#include <3dapi/Texture.h>
#include <3dapi/Vertex.h>
#include "TextView.h"

//#define PHONE_EMULATION
#define NORSK

enum States{
	CS_HOOKED,
	CS_WRITING_NAME,
	CS_PLAYING
};

//#define NO_CONSOLE

Scene::Scene(Geometry *_null, View *view) : Message(){
	#ifndef NO_CONSOLE
	Scores = new ScoreViews(view);
	Text = new TextView(view);
	#else
	Text = 0;
	Scores = 0;
	#endif

	null = _null;

//	null = new Geometry();
//	null->SetPosition(0,Vector(0,0,10000));

//	Geometry *null2 = new Geometry();
//	null->Node::Apply(0,null2);
//	null2->SetPosition(0,Vector(0,0,0));
//	null2->SetOrientation(0,Euler(0,0,0));

	camera = new Camera();
	camera->SetName(0,String("Camera"));
	null->Node::Apply(0,camera);
	CameraAI *camAI = new CameraAI(camera);
	camera->Apply(0,camAI);
	view->Attatch(camera);

	Geometry *Back = new Geometry();
	Back->Node::Apply(0,new Background(camera,Back));
	Back->SetPosition(0,Vector(0,0,8000*3));
	Back->Post();
	null->Node::Apply(0,Back);

	new Nebula(camera,null);
//#if 0
	new Sun(camera,null);
//#endif
//	new Planet(camera,null);
//#if 0
	new LensFlare(camera,null);
//#endif
	Intelligence::Apply(null);
	null->Node::Apply(0,this);
#if 0
//	Players = new DynamicArray();
/*
	for(int n=0; n<16; n++){
		Geometry *Ship = new Geometry();
		char name[1024];
		sprintf(name,"Player%d",n);
		Ship->SetName(String(name));	// fixme: Optimize!
		//Ship->SetPosition(Vector(0,0,-800000));
		Ship->Post();
		Players->Add(Ship);
		//AI_Player1 = new PlayerAI(Ship);
		null->Node::Apply(Ship);
		Ship->Node::Apply(new PlayerAI(Ship,Scores,Scores->GetPlayer(n)));
	}
*/
	for(int n=0; n<10; n++){
		Geometry *Rock = new Geometry();
		Rock->SetName(0,"Rock");
		Rock->Add(Vector(-400,-400,0));
		Rock->Add(Vector( 400,-400,0));
		Rock->Add(Vector( 400, 400,0));
		Rock->Add(Vector(-400, 400,0));
		Rock->Add(Vertex(0,0,0));
		Rock->Add(Vertex(1,1,0));
		Rock->Add(Vertex(2,1,1));
		Rock->Add(Vertex(3,0,1));
/* ////
		IndexedPolygon *pol = Rock->NewIndexedPolygon();
		pol->Add(0);
		pol->Add(1);
		pol->Add(2);
		pol->Add(3);
*/
		RockAI *AI_Rock = new RockAI(camera,/*this,*/Rock,400.0f);
		Rock->Node::Apply(0,AI_Rock);
		null->Node::Apply(0,Rock);
	}

	for(n=0; n<MAX_PLAYERS; n++){
		channels[n].state = CS_HOOKED;
		channels[n].name  = 0;
		channels[n].left  = false;
		channels[n].right = false;
		channels[n].num   = false;
		channels[n].st    = false;
		#ifndef THREAD_TEST
		Geometry *Ship = new Geometry();
		char name[1024];
		sprintf(name,"Player%d",n);
		Ship->SetName(0,String(name));
		//Ship->Post();
		channels[n].player = new PlayerAI(camera,Ship,Scores,Scores->GetPlayer(n),n);
		Ship->Node::Apply(0,channels[n].player);
		#endif
//printf("Player%d = %x,%x\n",);
		Players[n] = 0;
	}
#endif
#if 0
	MaterialCache = new DynamicArray();
	Material *mat = new Material("Textures/Ship/shipred",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat = new Material("Textures/Ship/shipyellow",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat = new Material("Textures/Ship/shipgreen",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat = new Material("Textures/Ship/shipcyan",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat = new Material("Textures/Ship/shippurple",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat = new Material("Textures/Ship/shipblue",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat = new Material("Textures/Ship/ship_lightmap/lm",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_SOURCE);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	for(n=0; n<MAX_PLAYERS; n++){
		char str[1024];
		sprintf(str,"Textures/interface/playernum/no%d",n+1);
		mat = new Material(str,Texture::cARGB);
		mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
		mat->CacheAll();
		#ifdef _DEBUG
		MaterialCache->Add(mat,__FILE__,__LINE__);
		#else
		MaterialCache->Add(mat);
		#endif
	}
	mat = new Material("Textures/Explosion/Explosion_0",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat = new Material("Textures/Explosion/Explosion_1",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat = new Material("Textures/Explosion/Explosion_2",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat = new Material("Textures/Explosion/Explosion_3",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat  = new Material("Textures/Ship/RStrobe",Texture::cRGB);
	mat->SetMode(MATERIAL_DEST_ADD_SOURCE);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat  = new Material("Textures/Ship/BStrobe",Texture::cRGB);
	mat->SetMode(MATERIAL_DEST_ADD_SOURCE);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat  = new Material("Textures/Boost/Flame",Texture::cRGB);
	mat->SetMode(MATERIAL_DEST_ADD_SOURCE|MATERIAL_SOURCE_DIFFUSE);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
/*
	mat = new Material("Textures/Shield1/Shield",Texture::cRGB);
	mat->SetMode(MATERIAL_DEST_ADD_SOURCE);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat = new Material("Textures/Shield2/Shield",Texture::cRGB);
	mat->SetMode(MATERIAL_DEST_ADD_SOURCE);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat = new Material("Textures/Shield3/Shield",Texture::cRGB);
	mat->SetMode(MATERIAL_DEST_ADD_SOURCE);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
*/	mat = new Material("Textures/shot",Texture::cARGB);
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	mat=new Material("Textures/Shield/Pickup/ShieldPickup",Texture::cARGB);//tv4logo/tv4logo");
	mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
	mat->CacheAll();
	#ifdef _DEBUG
	MaterialCache->Add(mat,__FILE__,__LINE__);
	#else
	MaterialCache->Add(mat);
	#endif
	for(n=0; n<4; n++){
		char name[1024];
		sprintf(name,"Textures/Rock_%d/Rock_%d",n,n);
		mat = new Material(name,Texture::cARGB);
		mat->SetMode(MATERIAL_SOURCE_DIFFUSE|MATERIAL_DEST_MULTIPLY_ONE_MINUS_ALPHA);
		mat->CacheAll();
		#ifdef _DEBUG
		MaterialCache->Add(mat,__FILE__,__LINE__);
		#else
		MaterialCache->Add(mat);
		#endif
	}
#endif
	Listen("/Devices/Input/Dialogic"); //Keyboard");
	Listen("/Devices/Input/Keyboard");
}

Scene::~Scene(){
//	delete Players;

	for(int n=0; n<MAX_PLAYERS; n++) delete channels[n].player;

	while(MaterialCache->GetCount()){
		Material *mat = (Material*)MaterialCache->GetItem(0);
		#ifdef _DEBUG
		MaterialCache->Remove(0,__FILE__,__LINE__);
		#else
		MaterialCache->Remove(0);
		#endif
		delete mat;
	}
	delete MaterialCache;

////	null->Node::Apply(0,(Intelligence*)0);	// fixme: Find a solution!
////	null->DoKill();
//	delete null;
	delete Scores;
	delete Text;	// fixme: Illagal free
}

bool Scene::Tick(double time){
//#if 0
	if(Text) Text->Tick(time);

	for(int n=0; n<MAX_PLAYERS; n++){
		switch(channels[n].state){
		case CS_HOOKED:
			if(Players[n]){
				Players[n]->GetNode()->Detatch(); //Kill(0); //delete Players[n];			// fixme: Crashes in disconnect now and then.
				Players[n]->GetNode()->SetVelocity(0,Vector(0,0,0));
				Players[n]=0;
			}
		break;
		case CS_WRITING_NAME:

			if(Players[n]){
				Players[n]->GetNode()->Detatch();
				Players[n]->GetNode()->SetVelocity(0,Vector(0,0,0));
				Players[n]=0;
			}

			#ifndef NO_CONSOLE
			if(Scores) if(!channels[n].name) channels[n].name = Scores->GetName(Scores->GetPlayer(n));
			#endif
			if(channels[n].left){
				channels[n].left = false;
				#ifdef NORSK
				channels[n].name[strlen(channels[n].name)-1]--;
				     if(channels[n].name[strlen(channels[n].name)-1]=='A'-1) channels[n].name[strlen(channels[n].name)-1] = 'Å';
				else if(channels[n].name[strlen(channels[n].name)-1]=='Å'-1) channels[n].name[strlen(channels[n].name)-1] = 'Ø';
				else if(channels[n].name[strlen(channels[n].name)-1]=='Ø'-1) channels[n].name[strlen(channels[n].name)-1] = 'Æ';
				else if(channels[n].name[strlen(channels[n].name)-1]=='Æ'-1) channels[n].name[strlen(channels[n].name)-1] = 'Z';
				#elif defined(SVENSK)
				name[strlen(name)-1]--;
				if(name[strlen(name)-1])=='a'-1) name[strlen(name)-1] = 'å';
				if(name[strlen(name)-1])=='å'-1) name[strlen(name)-1] = 'ö';
				if(name[strlen(name)-1])=='ö'-1) name[strlen(name)-1] = 'ä';
				if(name[strlen(name)-1])=='ä'-1) name[strlen(name)-1] = 'z';
				#else
				  if(channels[n].name[strlen(channels[n].name)-1]=='a') channels[n].name[strlen(channels[n].name)-1]='z';
				else channels[n].name[strlen(channels[n].name)-1]--;
				#endif
				#ifndef NO_CONSOLE
				Scores->SetScore(Scores->GetPlayer(n),0);
				#endif
			}
			if(channels[n].right){
				channels[n].right = false;
				#ifdef NORSK
				channels[n].name[strlen(channels[n].name)-1]++;
				//strlen(name)-1])=='Å'+1) name[strlen(name)-1] = 'Ø';
				//if(name[strlen(name)-1])=='Z'+1) name[strlen(name)-1] = 'Å';
				     if(channels[n].name[strlen(channels[n].name)-1]=='Z'+1) channels[n].name[strlen(channels[n].name)-1] = 'Æ';
				else if(channels[n].name[strlen(channels[n].name)-1]=='Æ'+1) channels[n].name[strlen(channels[n].name)-1] = 'Ø';
				else if(channels[n].name[strlen(channels[n].name)-1]=='Ø'+1) channels[n].name[strlen(channels[n].name)-1] = 'Å';
				else if(channels[n].name[strlen(channels[n].name)-1]=='Å'+1) channels[n].name[strlen(channels[n].name)-1] = 'A';
				#elif defined(SVENSK)
				name[strlen(name)-1]++;
				if(name[strlen(name)-1])=='z'+1) name[strlen(name)-1] = 'ä';
				if(name[len(name)-1])=='å'+1) name[strlen(name)-1] = 'a';
				#else
				  if(channels[n].name[strlen(channels[n].name)-1]=='z') channels[n].name[strlen(channels[n].name)-1]='a';
				else channels[n].name[strlen(channels[n].name)-1]++;
				#endif
				#ifndef NO_CONSOLE
				Scores->SetScore(Scores->GetPlayer(n),0);
				#endif
			}
			if(channels[n].num){
				channels[n].num = false;
				#ifndef NO_CONSOLE
				if(strlen(channels[n].name)==1) sprintf(channels[n].name,"Ano");
				else channels[n].name[strlen(channels[n].name)-1]='\0';
				#endif
				channels[n].state = CS_PLAYING;
				#ifndef NO_CONSOLE
				Scores->SetScore(Scores->GetPlayer(n),0);
				#endif

					#ifdef THREAD_TEST
					Geometry *Ship = new Geometry();
					char name[1024];
					sprintf(name,"Player%d",n);
					Ship->SetName(0,String(name));	// fixme: Optimize!
					//Ship->SetPosition(Vector(0,0,-800000));
					Ship->Post();
//					Players->Add(Ship);
					//AI_Player1 = new PlayerAI(Ship);
					null->Node::Apply(0,Ship);
					#ifndef NO_CONSOLE
					Ship->Node::Apply(0,new PlayerAI(camera,Ship,Scores,Scores->GetPlayer(n),n));
					#else
					Ship->Node::Apply(0,new PlayerAI(camera,Ship,0,0,n));
					#endif
					#else
					Geometry *Ship = channels[n].player->GetCreatorGeometry();
					null->Node::Apply(0,Ship);
					channels[n].player->Spawn();
					#endif
					Players[n]=Ship;

			}
			if(channels[n].st){
				channels[n].st = false;
				if(strlen(channels[n].name)==3){
					channels[n].state = CS_PLAYING;

					#ifdef THREAD_TEST
					Geometry *Ship = new Geometry();
					char name[1024];
					sprintf(name,"Player%d",n);
					Ship->SetName(0,String(name));	// fixme: Optimize!
					//Ship->SetPosition(Vector(0,0,-800000));
					Ship->Post();
//					Players->Add(Ship);
					//AI_Player1 = new PlayerAI(Ship);
					null->Node::Apply(0,Ship);
					#ifndef NO_CONSOLE
					Ship->Node::Apply(0,new PlayerAI(camera,Ship,Scores,Scores->GetPlayer(n),n));
					#else
					Ship->Node::Apply(0,new PlayerAI(camera,Ship,0,0,n));
					#endif
					#else
					Geometry *Ship = channels[n].player->GetCreatorGeometry();
					null->Node::Apply(0,Ship);
					channels[n].player->Spawn();
					#endif
					Players[n]=Ship;

				}
				else sprintf(channels[n].name,"%s%c",channels[n].name,channels[n].name[strlen(channels[n].name)-1]);
				#ifndef NO_CONSOLE
				Scores->SetScore(Scores->GetPlayer(n),0);
				#endif
			}
		break;
		}
	}
//#endif
	return false;
}

//#define TEST_ALL

void Scene::MessageReceived(void){
	int cnt = GetReceivedCount();
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
//printf("%s down\n",str);
			#ifdef PHONE_EMULATION
			if(!strcmp(str,"1")){
				channels[0].state = CS_WRITING_NAME;
				#ifndef NO_CONSOLE
				if(Scores){
					sprintf(Scores->GetName(Scores->GetPlayer(0)),"a");
					Scores->Activate(Scores->GetPlayer(0));
					Scores->SetScore(Scores->GetPlayer(0),0);
				}
				#endif
			}
			else if(!strcmp(str,"2")){
				channels[1].state = CS_WRITING_NAME;
				#ifndef NO_CONSOLE
				if(Scores){
					sprintf(Scores->GetName(Scores->GetPlayer(1)),"a");
					Scores->Activate(Scores->GetPlayer(1));
					Scores->SetScore(Scores->GetPlayer(1),0);
				}
				#endif
			}
			else if(!strcmp(str,"q")) channels[0].left  = true;
			else if(!strcmp(str,"w")) channels[0].right = true;
			else if(!strcmp(str,"a")) channels[0].st    = true;
			else if(!strcmp(str,"s")) channels[0].num   = true;
			else if(!strcmp(str,"i")) channels[1].left  = true;
			else if(!strcmp(str,"o")) channels[1].right = true;
			else if(!strcmp(str,"k")) channels[1].st    = true;
			else if(!strcmp(str,"l")) channels[1].num   = true;
			#endif
			if(len>2){
				int chan = str[1]-'0';
				if(chan<MAX_PLAYERS){
					str[1]='*';
					if(!strcmp(str,"C*_!Hook")){
						//printf("%d\n",chan);
	/*
						Geometry *Ship = new Geometry();
						char name[1024];
						sprintf(name,"Player%d",chan);
						Ship->SetName(String(name));	// fixme: Optimize!
						//Ship->SetPosition(Vector(0,0,-800000));
						Ship->Post();
	//					Players->Add(Ship);
						//AI_Player1 = new PlayerAI(Ship);
						null->Node::Apply(Ship);
						Ship->Node::Apply(new PlayerAI(Ship,Scores,Scores->GetPlayer(chan),chan));
	*/
						channels[chan].state = CS_WRITING_NAME;
						#ifndef NO_CONSOLE
						if(Scores){
							sprintf(Scores->GetName(Scores->GetPlayer(chan)),"A");
							Scores->Activate(Scores->GetPlayer(chan));
							Scores->SetScore(Scores->GetPlayer(chan),0);
						}
						#endif
					}
					else if(!strcmp(str,"C*_1")) channels[chan].left  = true;
					else if(!strcmp(str,"C*_2")) channels[chan].right = true;
					else if(!strcmp(str,"C*_*")) channels[chan].st    = true;
					else if(!strcmp(str,"C*_#")) channels[chan].num   = true;
					else if(len>3){
						chan = chan*10+(str[2]-'0');
						if(chan<MAX_PLAYERS){
							str[2]='*';
							if(!strcmp(str,"C**_!Hook")){
								channels[chan].state = CS_WRITING_NAME;
								#ifndef NO_CONSOLE
								if(Scores){
									sprintf(Scores->GetName(Scores->GetPlayer(chan)),"A");
									Scores->Activate(Scores->GetPlayer(chan));
									Scores->SetScore(Scores->GetPlayer(chan),0);
								}
								#endif
							}
							else if(!strcmp(str,"C**_1")) channels[chan].left  = true;
							else if(!strcmp(str,"C**_2")) channels[chan].right = true;
							else if(!strcmp(str,"C**_*")) channels[chan].st    = true;
							else if(!strcmp(str,"C**_#")) channels[chan].num   = true;
						}
					}
				}
			}
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
//printf("%s up\n",str);
			#ifdef PHONE_EMULATION
			     if(!strcmp(str,"q")) channels[0].left  = false;
			else if(!strcmp(str,"w")) channels[0].right = false;
			else if(!strcmp(str,"a")) channels[0].st    = false;
			else if(!strcmp(str,"s")) channels[0].num   = false;
			else if(!strcmp(str,"i")) channels[1].left  = false;
			else if(!strcmp(str,"o")) channels[1].right = false;
			else if(!strcmp(str,"k")) channels[1].st    = false;
			else if(!strcmp(str,"l")) channels[1].num   = false;
			#endif
			if(len>2){
				int chan = str[1]-'0';
				if(chan<MAX_PLAYERS){
					str[1]='*';
					if(!strcmp(str,"C*_!Hook")){
						//printf("%d\n",chan);
						channels[chan].state = CS_HOOKED;
						#ifndef NO_CONSOLE
						if(Scores){
							Scores->Deactivate(Scores->GetPlayer(chan));
							Scores->Update();
							Scores->SetScore(Scores->GetPlayer(chan),0);
						}
						#endif
					}
					else if(!strcmp(str,"C*_1")) channels[chan].left  = false;
					else if(!strcmp(str,"C*_2")) channels[chan].right = false;
					else if(!strcmp(str,"C*_*")) channels[chan].st    = false;
					else if(!strcmp(str,"C*_#")) channels[chan].num   = false;
					else if(len>3){
						int ch = chan*10+(str[2]-'0');
						if(ch<MAX_PLAYERS){
							str[2]='*';
							if(!strcmp(str,"C**_!Hook")){
								channels[ch].state = CS_HOOKED;
								#ifndef NO_CONSOLE
								if(Scores){
									Scores->Deactivate(Scores->GetPlayer(ch));
									Scores->Update();
									Scores->SetScore(Scores->GetPlayer(ch),0);
								}
								#endif
							}
							else if(!strcmp(str,"C**_1")) channels[ch].left  = false;
							else if(!strcmp(str,"C**_2")) channels[ch].right = false;
							else if(!strcmp(str,"C**_*")) channels[ch].st    = false;
							else if(!strcmp(str,"C**_#")) channels[ch].num   = false;
						}
					}
				}
			}
			delete str;
		}break;
		}
	}
}
