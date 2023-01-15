#include "Vampire.h"

void ScriptMain() {
	Api api = Api();
	Vampire vampire = Vampire();

	while (true) {
		vampire.tick();
		WAIT(0);
	}
}
