#pragma once

#include <chrono>
#include <fstream>
#include "ScriptDataModel.h"
#include "ScriptLogger.h"

using namespace std;

class ScriptDataManager
{
private:
	fstream dataFile;
	char* fileName;
	ScriptDataModel dataModel;

public:
	ScriptDataManager();
	void write(ScriptDataModel dataModel);
	ScriptDataModel read();
};
