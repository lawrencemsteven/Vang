#include "Vang/GraphicsAPI/GraphicsVulkan/VulkanHelpers/VulkanInstance.h"

#include "Vang.h"

namespace Vang::gfx::Vulkan {

	VulkanInstance::VulkanInstance(Window& window, std::string_view applicationName) {
		createInstance(window, applicationName);
	}

	VulkanInstance::~VulkanInstance() {}

	void VulkanInstance::createInstance(Window& window, std::string_view applicationName) {
		VkApplicationInfo appInfo{};
		appInfo.sType			   = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName   = applicationName.data();
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName		   = "Vang";
		appInfo.engineVersion	   = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion		   = VK_API_VERSION_1_2;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType			= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		VANG_FATAL("Test");

		glfwExtensions = window.getGraphicsAPIInstanceExtensions(&glfwExtensionCount);

		VANG_ERROR(glfwExtensionCount + "");
	}

}