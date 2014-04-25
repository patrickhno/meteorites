
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>

class Shock : Intelligence{
public:				Shock(class PlayerAI *, class Vector &);
					~Shock();
		bool		Tick(double time);
private:
		double		Spawn;
class	Material	*mat;
};

