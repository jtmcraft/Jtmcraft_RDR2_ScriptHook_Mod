#include "Vampire.h"

void ScriptMain() {
	Vampire vampire = Vampire();

	while (true) {
		vampire.tick();
		WAIT(0);
	}
}
