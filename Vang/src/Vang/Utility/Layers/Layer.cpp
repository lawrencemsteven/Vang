#include "Layer.h"

namespace Vang::Utility::Layers {

	Layer::Layer(const std::string& name)
		: m_debugName{name} {}

	Layer::~Layer() {}

	const std::string& Layer::getName() const {
		return m_debugName;
	}

}