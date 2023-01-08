#include "NativesWrapper.h"

Hash NativesWrapper::getHash(char* key) {
	return GAMEPLAY::GET_HASH_KEY(key);
}

char* NativesWrapper::literalString(char* str) {
	return GAMEPLAY::CREATE_STRING(10, "LITERAL_STRING", str);
}
