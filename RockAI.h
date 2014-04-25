
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>
//#include "KernelClient.h"

class RockAI : public Intelligence{//, KernelClient{
public:			RockAI(class Camera *,/*class Meteorites *,*/ class Geometry *, float);
				RockAI(/*Meteorites *,*/ Geometry *, RockAI *);
				~RockAI();
Intelligence	*Clone(Geometry *);
		bool	Tick(double time);
//		void	MessageReceived(double time, int Cmd, void *);
		bool	BoundingSphereIntersection(float sqrdist, class Node *caller);
private:
		Camera		*camera;
		Vector		PositionStep;
		double		OldTime,ImpactTime;
//		float	lastpulse;
//		bool		Kill;
		int			startframe;
		Material	*RockMaterial;
		Material	*ExplotionMaterial[4];
		double		ExpTime;
//		Meteorites	*scr;
		int			status;
		float		size;
		bool		exploding;
		int			explotion;
};

