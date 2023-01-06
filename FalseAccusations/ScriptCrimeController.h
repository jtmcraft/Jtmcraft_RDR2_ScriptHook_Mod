#pragma once

#include "script.h"
#include "ScriptDataModel.h"

using namespace std;

const Hash CRIMES[] = {
	0xA54C77E0,
	0xA2FF1145,
	0x5011F613,
	0x12C1D589,
	0x55AD2BEB,
	0xE28ECE7E,
	0xA3BEDE4C,
	0xFC738E61,
	0x72ADE410,
	0x45DB39D8,
	0xAEDE8E35,
	0x5098CC5A
};

class ScriptCrimeController
{
private:
	ScriptDataModel dataModel;

public:
	ScriptCrimeController();
	ScriptDataModel getDataModel();
	void setDataModel(ScriptDataModel dataModel);
	Hash randomCrime();
};
