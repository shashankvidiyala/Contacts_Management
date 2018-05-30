#include "server.h"

void pushtohead(char *username, vectori<MyStruct> cache){
	pushtodb(username, &cache[0], cache.size());
}


