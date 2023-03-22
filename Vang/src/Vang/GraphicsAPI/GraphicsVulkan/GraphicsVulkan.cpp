#include "Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.h"

#include "Vang.h"

namespace Vang {

	GraphicsVulkan::GraphicsVulkan(VangInst& vangInst)
		: GraphicsAPI{vangInst},
		  m_vulkanInstance{
			  std::make_unique<VulkanInstance>(m_vangInst.getWindow(), m_applicationName)} {
		initialize();
	}

	GraphicsVulkan::GraphicsVulkan(VangInst& vangInst, std::string_view applicationName)
		: GraphicsAPI{vangInst, applicationName},
		  m_vulkanInstance{
			  std::make_unique<VulkanInstance>(m_vangInst.getWindow(), m_applicationName)} {
		initialize();
	}

	GraphicsVulkan::~GraphicsVulkan() { cleanup(); }

	void GraphicsVulkan::beginFrame() {}

	void GraphicsVulkan::initialize() { VANG_DEBUG("Initializing Vulkan"); }

	void GraphicsVulkan::cleanup() { VANG_DEBUG("Closing Vulkan"); }

}
