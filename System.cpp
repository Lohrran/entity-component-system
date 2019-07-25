#include "System.h"

System::System(std::vector<std::type_index> req) : requeriments{ req } { }

std::vector<std::type_index> System::getRequeriments()
{
	return requeriments;
}

void System::configure(EventChannel* evt, Scene* scn) 
{ 
	eventChannel = evt; 
	scene = scn; 
}