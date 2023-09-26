#pragma once

#include "Event.h"

namespace Vang::Windowing {

	class EventHandler {
	public:
		void onEvent(Vang::Windowing::Event& e);
	};

}