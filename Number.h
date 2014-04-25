
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>

class Number : Intelligence{
public:				Number(class Camera *, class PlayerAI *ship, int);
					~Number();
		void		Activate(void);
		bool		Tick(double time);
private:
		Camera		*camera;
class	PlayerAI	*ship;
class	Material	*mat;
//		bool		active;
		double		OldTime;
		float		trans;
};

