
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>

class Background : public Intelligence{ // , KernelClient{
public:				Background(class Camera *, class Geometry *);
					~Background();
		bool		Tick(double time);
private:
class	Material	*BackMaterial;
class	Camera		*camera;
};

