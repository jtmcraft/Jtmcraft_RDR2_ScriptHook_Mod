#pragma once

#include "../../inc/types.h"
#include "../../inc/natives.h"
#include "NativesWrapper.h"

class UiNotification
{
private:
	NativesWrapper nativesWrapper;
	void notificationRight(char* text, char* dict, char* icon, char* colour, int duration);
	void notificationTopLeft(char* text, int duration);

public:
	UiNotification();
	void notifyInfo();
	void notifyHeadShot();
};
