#pragma once

#include "Vang/GraphicsAPI/GraphicsAPI.h"
#include "Vang/GraphicsAPI/GraphicsVulkan/VulkanHelpers/VulkanInstance.h"

class VangInst;

namespace Vang::gfx::Vulkan {

	class GraphicsVulkan : public GraphicsAPI {
	public:
		GraphicsVulkan() = delete;
		GraphicsVulkan(VangInst& vangInst);
		GraphicsVulkan(VangInst& vangInst, std::string_view applicationName);
		~GraphicsVulkan();
		GraphicsVulkan(const GraphicsVulkan&)		 = delete;
		GraphicsVulkan(GraphicsVulkan&&)			 = delete;
		GraphicsVulkan& operator=(const GraphicsVulkan&) = delete;
		GraphicsVulkan& operator=(GraphicsVulkan&&)		 = delete;

		void beginFrame() override;

	private:
		void initialize();
		void cleanup();

		std::unique_ptr<VulkanInstance> m_vulkanInstance;
	};

}
