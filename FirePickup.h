
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>
#include <Interface/KernelClient.h>

class FirePickup : public Intelligence , KernelClient{
public:				FirePickup(class Camera *, Geometry *);
					~FirePickup();
		bool		Tick(double time);
//		void		MessageReceived(double time, int Cmd, void *);
		bool		BoundingSphereIntersection(float sqrdist, class Node *caller);
private:
class	Camera		*camera;
		double		StartTime;
class	Material	*mat;
		bool		KillMe;
};

