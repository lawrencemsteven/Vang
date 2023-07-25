#pragma once

#include "Layer.h"

namespace Vang {

	class LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin();
		std::vector<Layer*>::iterator end();

	private:
		std::vector<Layer*> m_layers;
		unsigned int m_layerInsertIndex = 0;
	};

}