#pragma once

#include "Vang/Window/Window.h"

#include "vulkan/vulkan.h"

namespace Vang::gfx::Vulkan {

	class VulkanInstance {
	public:
		VulkanInstance(const Window& window, std::string_view applicationName = "");
		~VulkanInstance();

	private:
		void createInstance(const Window& window, std::string_view applicationName);
		std::vector<const char*> getRequiredExtensions(const Window& window);
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		bool checkValidationLayerSupport();

		VkInstance m_instance;
	};

}
