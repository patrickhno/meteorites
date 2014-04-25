
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>

class LensFlare : Intelligence{
public:				LensFlare(class Camera *, Geometry *);
					~LensFlare();
		bool		Tick(double time);
private:
		Camera		*camera;
class	Material	*mat,*ring1,*ring2,*ring3,*halo;
class	Geometry	*geo;
};


