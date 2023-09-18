#include "Vang/GraphicsAPI/GraphicsVulkan/VulkanHelpers/VulkanInstance.h"

#include "Vang.h"

namespace Vang::gfx::Vulkan {

	const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

	VulkanInstance::VulkanInstance(std::string_view applicationName) {
		createInstance(applicationName);
	}

	VulkanInstance::~VulkanInstance() { vkDestroyInstance(m_instance, nullptr); }

	void VulkanInstance::createInstance(std::string_view applicationName) {
#ifdef VANG_GRAPHICSAPI_VULKAN_VALIDATION_LAYERS
		if (!checkValidationLayerSupport()) {
			VANG_FATAL("Validation layers requested, but not available!");
		}
#endif
		Vang::Windowing::Window& window = VangInst::Get().getWindow();

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

		auto extensions = getRequiredExtensions(window);

		createInfo.enabledExtensionCount   = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

#ifdef VANG_GRAPHICSAPI_VULKAN_VALIDATION_LAYERS
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		createInfo.enabledLayerCount   = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();

		populateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
#else
		createInfo.enabledLayerCount = 0;

		createInfo.pNext = nullptr;
#endif
		if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
			std::cout << vkCreateInstance(&createInfo, nullptr, &m_instance) << std::endl;
			VANG_FATAL("Failed to create Vulkan instance!");
		}

#ifdef VANG_GRAPHICSAPI_VULKAN_VALIDATION_LAYERS
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
		populateDebugMessengerCreateInfo(debugCreateInfo);

		if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) !=
			VK_SUCCESS) {
			VANG_FATAL("failed to set up debug messenger!");
		}
#endif
	}

	std::vector<const char*> VulkanInstance::getRequiredExtensions(const Vang::Windowing::Window& window) {
		uint32_t windowExtensionCount = 0;
		const char** windowExtensions;

		windowExtensions = window.getGraphicsAPIInstanceExtensions(&windowExtensionCount);

		std::vector<const char*> extensions{windowExtensions,
											windowExtensions + windowExtensionCount};

#ifdef VANG_GRAPHICSAPI_VULKAN_VALIDATION_LAYERS
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

		return extensions;
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL
	debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				  VkDebugUtilsMessageTypeFlagsEXT messageType,
				  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}

	void VulkanInstance::populateDebugMessengerCreateInfo(
		VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
		createInfo				   = {};
		createInfo.sType		   = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
									 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
									 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
								 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
								 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = debugCallback;
	}
	bool VulkanInstance::checkValidationLayerSupport() {
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers) {
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}

			if (!layerFound) { return false; }
		}

		return true;
	}
}