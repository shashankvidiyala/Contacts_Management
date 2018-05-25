#include "server.h"

void pushtohead(char *username, std::vector<MyStruct> cache){
	pushtodb(username, &cache[0], cache.size());
}


