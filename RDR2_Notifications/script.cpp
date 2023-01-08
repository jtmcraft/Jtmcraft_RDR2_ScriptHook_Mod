#pragma once

#include "script.h"
#include "keyboard.h"
#include "UiNotification.h"

using namespace std;

void ScriptMain() {
	UiNotification uiNotification = UiNotification();

	while (true) {
		if (IsKeyJustUp(VK_KEY_Y)) {
			uiNotification.notifyInfo();
		}

		WAIT(0);
	}
}
