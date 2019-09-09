#ifndef EVENTCHANNEL_H
#define EVENTCHANNEL_H

#include <map>
#include <vector>
#include <typeindex>

#include "HandlerFunction.h"

class EventChannel
{
	public:
		EventChannel() = default;
		EventChannel(const EventChannel&) = default;
		EventChannel& operator = (const EventChannel&) = delete;
		EventChannel& operator = (EventChannel&&) = delete;

		~EventChannel();
	
		template <typename EventType>
		void publish(EventType* evt);

		template <typename E, typename EventType>
		void subscribe(E* Instance, void (E::*function)(EventType*));

	private:
		std::map<std::type_index, std::vector<FunctionBase*>>subscribers;
};

template <typename EventType>
inline void EventChannel::publish(EventType* evt)
{
	std::type_index eventType = std::type_index(typeid(EventType));

	if (subscribers[eventType].empty()) { return; }
	
	for (auto &function : subscribers[eventType])
	{
		if (function != nullptr)
		{
			function->execute(evt);
		}
	}
}

template <typename E, typename EventType>
inline void EventChannel::subscribe(E* Instance, void (E::*function)(EventType*))
{
	std::type_index eventType = std::type_index(typeid(EventType));

	subscribers[eventType].push_back(new HandlerFunction<E, EventType>(Instance, function));
}
#endif