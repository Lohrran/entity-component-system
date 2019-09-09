#include "EventChannel.h"

EventChannel::~EventChannel()
{
	// Delete all systems created
	while (!subscribers.empty())
	{
		std::type_index eventType = subscribers.begin()->first;
		std::vector<FunctionBase*> functionBases = subscribers.find(eventType)->second;
			
		while (!functionBases.empty())
		{
			FunctionBase* func = functionBases.back();
			functionBases.erase(std::remove(functionBases.begin(), functionBases.end(), func), functionBases.end());
			delete func;
		}

		functionBases.clear();
		subscribers.erase(eventType);
	}
}