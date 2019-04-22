#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
	public:
		Component() : enabled{ true } { }
		virtual ~Component() = default;

		bool enabled;
};
#endif