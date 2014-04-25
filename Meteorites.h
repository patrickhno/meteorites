
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

//#include <3dapi/Network/Client.h>
#include <3dapi/Network/Message.h>

class Meteorites : /*Client,*/ Message{
public:				Meteorites();
					~Meteorites();
		void		InitLevels(int);
		void		NextLevel(int);
		void		MessageLoop(void);
//		void		MessageReceived(double time, int Cmd, void *);
		void		MessageReceived(void);
//private:
		void		Refresh(class WindowScreen *);
		int			AttatchHook,
					DetatchHook,
					ShutDownHook;
class	DynamicArray
					*Rocks,
					*Rocks_sub,
					*Rocks_sub_sub,
					*AI_Rocks,
					*PlayerGeometries,
					*InfoViews,
					*ViewBunch,
					*BitmapBunch;
		int			Rocks_item,
					Rocks_sub_item,
					Rocks_sub_sub_item;
		int			RockCount;
class	View		*View1,
					*View2,
					*View4; //,*ScoreView;
class	Bitmap		*MeteoritesBitmap;
class	Geometry	*null,
					*Back;
class	PlayerAI	*AI_Player1,
					*AI_Player2,
					*AI_Player3,
					*AI_Player4;
class	Camera		*cam;
class	CameraAI	*camAI;
		bool		quit,allowquit;
class	Font		*font;
//struct	RefreshArgs *rfargs;
		bool		bailout;
class	Bitmap		*Info1,*Info2,*Info3;
class	ScoreViews	*Scores;
class	Scene		*scene;
class	WindowScreen *scr;
		#ifdef	TV2
		View		*tv2v;
		Bitmap		*tv2bm;
		#endif
		#ifdef	SCHIBSTED
		View		*tv2v;
		Bitmap		*tv2bm;
		#endif
class	PhoneNumber	*pnum;
//class	Message		*msg;
class	Message		*msg;
};
