
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <3dapi/Network/Message.h>
#include <3dapi/Inteligence.h>

struct ChannelState{
enum	States		state;
		bool		left,right,num,st;
		char		*name;
class	PlayerAI	*player;
};

class Scene : Message, public Intelligence{
public:		Scene(class Geometry *, class View *);
			~Scene();
	bool	Tick(double);
	void	MessageReceived(void);
private:
//	int		channels[16];
		Camera		*camera;
	ChannelState	channels[MAX_PLAYERS];
class	Geometry	*null;
class	ScoreViews	*Scores;
class	DynamicArray *MaterialCache;
class	Geometry	*Players[MAX_PLAYERS];
class	TextView	*Text;
};

