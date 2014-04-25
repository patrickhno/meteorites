
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>
#include <3dapi/Euler.h>

class CameraAI : public Intelligence{ //, KernelClient{
public:			CameraAI(Camera *);
				~CameraAI();
		bool	Tick(double time);
private:
		Vector		PositionStep,Ofs,vel;
		double		OldTime;
		Euler		Orientation;
};
