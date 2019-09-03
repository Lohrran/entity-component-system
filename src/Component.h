#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
	public:
		Component() : enabled{ true } { }

		Component(const Component&) = default;
		Component& operator = (const Component&) = default;
		Component& operator = (Component&&) = default;
		virtual ~Component() = default;

		bool enabled;
};
#endif