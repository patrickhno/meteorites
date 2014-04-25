
// Copyright (C) 1997-1998 RealityMakers Entertainment as
// All rights reserved.

#include <Interface/View.h>
#include <3dapi/Network/Message.h>

class PhoneNumber : View, Message{
public:			PhoneNumber(View *);
				~PhoneNumber();
		void	MessageReceived(void);
private:
class	Font	*font,*font2;
		View	*price;
};

