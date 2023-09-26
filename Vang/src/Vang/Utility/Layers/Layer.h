#pragma once

#include "Vang/Utility/Events/Event.h"

namespace Vang::Utility::Layers {

	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Vang::Utility::Events::Event& event) {}

		const std::string& getName() const;

	protected:
		std::string m_debugName;
	};

}