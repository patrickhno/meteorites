#if 0

// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>
#include <3dapi/GeoMath.h>

class BoostAI : public Intelligence{ // , KernelClient{
public:			BoostAI(Geometry *, Geometry *ship);
				~BoostAI();
		bool	Tick(double time);
		void	Activate(void);
		void	Deactivate(void);
private:
class	Material	*Boost;
		Vector		OldVelocity;
class	Geometry	*ship,*geo;
class	IndexedPolygon	*pol;
};

#endif
