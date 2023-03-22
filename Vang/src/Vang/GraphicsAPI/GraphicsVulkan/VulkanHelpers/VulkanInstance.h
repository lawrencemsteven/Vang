#pragma once

#include "Vang/Window/Window.h"

#include "vulkan/vulkan.h"

namespace Vang {

	class VulkanInstance {
	public:
		VulkanInstance(Window& window, std::string_view applicationName = "");
		~VulkanInstance();

	private:
		void createInstance(Window& window, std::string_view applicationName);

		VkInstance m_instance;
	};

}
