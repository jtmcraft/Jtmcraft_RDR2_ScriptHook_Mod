#pragma once

#include <sstream>
#include "../../inc/types.h"
#include "Api.h"
#include "ScriptDataModel.h"

class ScriptInfoPanel
{
private:
	Api api;

public:
	ScriptInfoPanel();
	void tick(ScriptDataModel dataModel);
};
