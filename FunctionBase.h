#ifndef FUNCTIONBASE_H
#define FUNCTIONBASE_H

#include "Event.h"

class FunctionBase
{
	public:
		void execute(Event* evt) { call(evt); }

	private:
		virtual void call(Event* evt) = 0;
};
#endif