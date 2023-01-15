#include "SnowBlanket.h"

void ScriptMain() {
	SnowBlanket snowBlanket = SnowBlanket();

	while (true) {
		snowBlanket.tick();
		WAIT(0);
	}
}
