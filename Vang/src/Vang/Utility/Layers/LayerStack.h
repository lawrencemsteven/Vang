#pragma once

#include "Layer.h"

namespace Vang::Utility::Layers {

	class LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void update();
		void onEvent(Vang::Utility::Events::Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

	private:
		std::vector<Layer*> m_layers;
		unsigned int m_layerInsertIndex = 0;
	};

}