#include "EventHandler.h"

#include "Vang.h"

namespace Vang::Utility::Events {

	void EventHandler::onEvent(Event& e) {
		Vang::getLayerStack().onEvent(e);
	}
}