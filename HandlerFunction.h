#ifndef HANDLERFUNCTION_H
#define HANDLERFUNCTION_H

#include "FunctionBase.h"

template <typename E, typename EventType>
class HandlerFunction : public FunctionBase
{
	public:
		typedef void (E::*Function)(EventType*);

		HandlerFunction(E* Instance, Function function) : Instance{ Instance }, function{ function } { }

		void call(Event* evt) override {	(Instance->*function)(static_cast<EventType*>(evt));	}

	private:
		E* Instance;
		Function function;
};
#endif