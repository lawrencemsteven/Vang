#include "EventHandler.h"

#include "Vang.h"

namespace Vang::Windowing {

	void EventHandler::onEvent(Vang::Windowing::Event& e) {
		Vang::getLayerStack().onEvent(e);
	}
}