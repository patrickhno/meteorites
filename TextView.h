
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

class TextView : Message{
public:			TextView(class View *);
				~TextView();
		void	Tick(double);
protected:
virtual	void	MessageReceived(void);
private:
		char	testText[1024*100];
		int		offset;
		double	t_start;
		View	*view;
		char	*text;
class	Font	*font;
		View	*parent;
class	DynamicArray	*Transitions,*images;
		float	delay;
		char	*textptr;
};

