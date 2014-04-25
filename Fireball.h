
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>

class Fireball : public Intelligence{
public:			Fireball(class Geometry *, class PlayerAI *);
				~Fireball();
		bool	Tick(double time);
		bool	BoundingSphereIntersection(float sqrdist, class Node *caller);
private:
		double	SpawnTime;
class	PlayerAI	*mother;
		bool	Explode;
class	Material *expm;
		float	Speed;
};
