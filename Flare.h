
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>
#include <Interface/String.h>

class Flare : public Intelligence{
public:				Flare(class Geometry *, class PlayerAI *, void *, class ScoreViews *);
					~Flare();
		bool		Tick(double time);
		bool		BoundingSphereIntersection(float sqrdist, class Node *caller);
class	Vector		*GetVelocity(void);
private:
		double		SpawnTime,spawnsparcle,oldtime;
class	PlayerAI	*mother;
//		char		mother_name[10];
//class	Material	*expm;
		bool		Explode;
		float		Speed;
		Vector		Velocity;
class IndexedPolygon *pol;
class	ScoreViews	*Scores;
		void		*player;
		String		mother_name;
};
