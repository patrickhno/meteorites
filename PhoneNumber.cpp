
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <posix/stdlib.h>
#include <posix/stdio.h>
#include <posix/string.h>
#include <Interface/Font.h>
#include "PhoneNumber.h"

PhoneNumber::PhoneNumber(View *parent) : View(Rect(.3f,0,.7f,.2f)), Message(){
	SetName("PhoneNumber");
	SetClearState(false);
	
	SetColor(ARGB(.7f,.35f,.0f));
	//SetColor(ARGB(.0.25f,.25f,.7f));

	//font = new Font("Fonts/swiss");
	font = new Font("Fonts/Arial_Black_35"); //swiss");   //arial15pt1");
	font->SetSize(.06f);
	/*ConsoleStream::*/Apply(font);
	Print("Error!");
	parent->Apply(this);

	price = new View(Rect(.1f,.25f,0.7f,.35f));
//	font2 = new Font("Fonts/swiss");
	font2 = new Font("Fonts/Arial_Black_35"); //swiss");   //arial15pt1");
	font2->SetSize(.02f);
	price->/*ConsoleStream::*/Apply(font2);
	price->SetClearState(false);

	price->SetColor(ARGB(.7f,.35f,.0f));
	//price->SetColor(ARGB(.0.25f,.25f,.7f));
	//price->SetColor(ARGB(.7f,.7f,.7f));
	
	price->Print("Error!");
	Apply(price);
}

PhoneNumber::~PhoneNumber(){
	delete font;
	delete price;
	delete font2;
}

void PhoneNumber::MessageReceived(void){
	char *buf = (char*)GetReceivedBuffer();
	float rate = *(float*)buf; buf = (char*)(int(buf)+sizeof(float));
	float connect = *(float*)buf; buf = (char*)(int(buf)+sizeof(float));
	int len = *(int16*)buf; buf = (char*)(int(buf)+sizeof(int16));
	char *str = new char[1024]; //len+1];
	sprintf(str,"Ring ");
	int l = strlen(str);
	for(int n=l; n<len+l; n++) str[n]=buf[n-l];
	str[len+l]=0;
	ConsoleStream::Clear();
	Print(str);
	if(connect>0) sprintf(str,"(Kr. %3.2f oppkobling. Kr. %3.2f pr. min.)",connect,rate);
	else sprintf(str,"             (Kr. %3.2f pr.min.)",rate);
	price->ConsoleStream::Clear();
	price->Print(str);
	delete str;
}


