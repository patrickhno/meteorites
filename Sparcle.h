
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>

class Sparcle : public Intelligence{
public:			Sparcle(class Flare *);
				~Sparcle();
		bool	Tick(double time);
private:
		double	Spawn,oldtime;
		Vector	Velocity;
class	Flare	*parent;
};
