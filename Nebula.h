
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>

class Nebula : Intelligence{
public:				Nebula(class Camera *, class Geometry *);
					~Nebula();
		bool		Tick(double time);
private:
		Camera		*camera;
class	Material	*mat;
};

