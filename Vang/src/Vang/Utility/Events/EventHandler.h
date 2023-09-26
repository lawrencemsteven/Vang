#pragma once

#include "Event.h"

namespace Vang::Utility::Events {

	class EventHandler {
	public:
		EventHandler()								 = default;
		~EventHandler()								 = default;
		EventHandler(const EventHandler&)			 = delete;
		EventHandler(EventHandler&&)				 = delete;
		EventHandler& operator=(const EventHandler&) = delete;
		EventHandler& operator=(EventHandler&&)		 = delete;

		void onEvent(Event& e);
	};

}