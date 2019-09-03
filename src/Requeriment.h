#ifndef REQUERIMENT_H
#define REQUERIMENT_H

#include "System.h"

template <typename ...COMPONENTS>
class Requeriment : public System
{
	public:
		Requeriment() : System({ typeid (const COMPONENTS)... }) { }

		Requeriment& operator = (const Requeriment&) = default;
		Requeriment& operator = (Requeriment&&) = default;
		virtual ~Requeriment() = default;
};
#endif