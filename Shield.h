
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>

class ShieldAI : public Intelligence{ // , KernelClient{
public:			ShieldAI(Geometry *);
				~ShieldAI();
		bool	Tick(double time);
		void	Collide(double time);
		void	Activate(void);
		void	Deactivate(void);
		bool	Active(void);
private:
		bool		activate;
		double		Activated;
		double		ColTime;
class	Material	*Shield1;
		Material	*Shield2;
		Material	*Shield3;
		Material	*Shield4;
		float		StartTime;
class IndexedPolygon *pol1,*pol2,*pol3;
class	Geometry	*geo;
};

