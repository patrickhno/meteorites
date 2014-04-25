#if 0

// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>

class RedStrobeAI : public Intelligence{ // , KernelClient{
public:			RedStrobeAI(Geometry *);
				~RedStrobeAI();
		bool	Tick(double time);
		void	Activate(void);
		void	Deactivate(void);
private:
class	Material	*RedStrobe;
		float	pulse;
class	IndexedPolygon	*pol;
class	Geometry		*geo;
};

#endif
