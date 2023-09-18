#pragma once

#include "Vang/Window/Window.h"
#include "Vang/GraphicsAPI/GraphicsVulkan/VulkanHelpers/VulkanSurface.h"

#include "vulkan/vulkan.h"

namespace Vang::gfx::Vulkan {

	class VulkanInstance {
	public:
		VulkanInstance(std::string_view applicationName = "");
		~VulkanInstance();

	private:
		void createInstance(std::string_view applicationName);
		std::vector<const char*> getRequiredExtensions(const Vang::Windowing::Window& window);
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		bool checkValidationLayerSupport();

		VkInstance m_instance;

#ifdef VANG_GRAPHICSAPI_VULKAN_VALIDATION_LAYERS
		VkDebugUtilsMessengerEXT m_debugMessenger
#endif
	};

}
