
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>

class Planet : Intelligence{
public:				Planet(class Camera *, class Geometry *);
					~Planet();
		bool		Tick(double time);
private:
		Camera		*camera;
class	Material	*mat;
};

