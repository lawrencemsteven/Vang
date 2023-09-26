#pragma once

#include "Layer.h"

namespace Vang::Utility::Layers {

	class LayerStack {
	public:
		LayerStack();
		~LayerStack();
		LayerStack(const LayerStack&)			 = delete;
		LayerStack(LayerStack&&)				 = delete;
		LayerStack& operator=(const LayerStack&) = delete;
		LayerStack& operator=(LayerStack&&)		 = delete;

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