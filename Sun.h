
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>

class Sun : Intelligence{
public:				Sun(class Camera *, Geometry *);
					~Sun();
		bool		Tick(double time);
private:
		Camera		*camera;
class	Material	*mat1,*mat2;
};


