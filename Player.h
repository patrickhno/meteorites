
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Inteligence.h>
#include <3dapi/Network/Message.h>
#include <3dapi/Euler.h>

class PlayerAI : public Intelligence, Message{ // , KernelClient{
public:			PlayerAI(class Camera *, Geometry *, class ScoreViews *, void *, int);
				~PlayerAI();
		void	Spawn(void);
		bool	Tick(double time);
		void	MessageReceived(double time, int Cmd, void *);
//		Vector	*GetVelocity(void);
		bool	BoundingSphereIntersection(float sqrdist, class Node *caller);
		void	MessageReceived(void);

		void	AddScore(int);
		void	Explode(void);
		bool	IsAlive(void);

		enum{
			ADD_SCORE = 100
		};
private:
		float		redpulse,bluepulse;
		Camera		*camera;
friend	class		CameraAI;
		Euler		OrientationAx;
		Euler		OrientationStep;
		Euler		Orientation;
//		Vector		Velocity;
		Vector		Acceleration;

class	Material	*LightMaterial,*NumberMaterial;
		bool		bounce,activate_shield;
		Vector		BounceDirection;
		char		*AddBind;
		char		*SubBind;
		char		*NextBind;
		char		*HookBind;
		char		*NumberBind;
		char		*AvsluttBind;
		char		*LeftBind;
		char		*RightBind;
//		int			BoostHook;
//		int			YawHook;
//		int			FireHook;
		//Quaternion	OrientationAx;
		//Quaternion	OrientationStep;
		double		OldTime;
		//Geometry	*FireballGeo;
//bool	fire;
		double		LastFire;
float	pulse;
class	Material	*ShipMaterial;
		float		health;
//		Material	*ExplotionMaterial;
		double		ExpTime;
//		bool		state;
		float		rate;
		int			RateHook;
		double		StartTime;
		bool		shield;
//		Geometry	*RedStrobe;
//		Geometry	*BlueStrobe;
		Material	*RedStrobe;
		Material	*BlueStrobe;
//		Geometry	*LeftBoost;
//		Geometry	*RightBoost;
		Material	*Boost;
		Material	*Shield1;
		Geometry	*Shield;
class	ShieldAI	*shieldAI;
class	SoundPoint	*Sound;

		bool		addchar,subchar,nextchar,hook,number,avslutt,left,right;
		bool		wrotename;
//class	View		*view;
		int			score;
class	Number		*num;
//		char		name[50];
		char		*name;
		float		charge;
class	ScoreViews	*Scores;
		void		*player;
		int			playernum;
enum	States		state;
		double		ExplodeTime;
class	IndexedPolygon	*pol1,*pol2,*BoostPoly1,*BoostPoly2,*redpol,*bluepol,*shieldpol;
class	Material	*expm;
class	Geometry	*geo;
		Vector		OldVelocity;
		double		ShieldStart;
		bool		shield_active;
};

