
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

//#include <Interface/Semaphore.h>

class ScoreViews{ // : Semaphore{
public:					ScoreViews(class View *);
						~ScoreViews();
//class	View			*GetView(int n);
		void			*GetPlayer(int num);
		void			SetScore(void *_pl, int val);
		char			*GetName(void *_pl);
		void			Update(void);
		void			Activate(void *);
		void			Deactivate(void *);
		bool			IsActive(void *);
private:
class	DynamicArray	*Views;
class	Font			*font;
class	DynamicArray	*BitmapBunch;
class	DynamicArray	*ViewBunch;
class	Players			*players;
		struct HiScore{
			int			score[10];
			char		name[10][4];
		} hiscore;
		int				connect_log[MAX_PLAYERS];
class	Message			*msg;
};

