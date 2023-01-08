#pragma once

#include "../../inc/types.h"
#include "../../inc/natives.h"

class NativesWrapper
{
public:
	Hash getHash(char* key);
	char* literalString(char* str);
};
