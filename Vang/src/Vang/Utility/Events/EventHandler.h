#pragma once

#include "Event.h"

namespace Vang::Utility::Events {

	class EventHandler {
	public:
		void onEvent(Event& e);
	};

}