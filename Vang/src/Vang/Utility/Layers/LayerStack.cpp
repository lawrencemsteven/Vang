#include "LayerStack.h"

namespace Vang::Utility::Layers {

	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_layers) {
			delete layer;
		}
	}

	void LayerStack::update() {
		for (Layer* layer : m_layers) {
			layer->onUpdate();
		}
	}

	void LayerStack::onEvent(Vang::Utility::Events::Event& e) {
		for (auto it = m_layers.end(); it != m_layers.begin();) {
			(*--it)->onEvent(e);
			if (e.handled)
				break;
		}
	}

	void LayerStack::pushLayer(Layer* layer) {
		m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
		m_layerInsertIndex++;
		layer->onAttach();
	}

	void LayerStack::pushOverlay(Layer* overlay) {
		m_layers.emplace_back(overlay);
		overlay->onAttach();
	}

	void LayerStack::popLayer(Layer* layer) {
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end()) {
			m_layers.erase(it);
			m_layerInsertIndex--;
			layer->onDetach();
		}
	}

	void LayerStack::popOverlay(Layer* overlay) {
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end()) {
			m_layers.erase(it);
			overlay->onDetach();
		}
	}
}