include(CMakeFiles.cmake)

add_library(Vang STATIC ${Vang_FILES})

target_compile_features(Vang PUBLIC cxx_std_20)

source_group("Vang" FILES ${Vang_Vang})
source_group("Vang/Utility/Camera" FILES ${Vang_UTILITY_CAMERA})
source_group("Vang/Utility/Logging" FILES ${Vang_UTILITY_LOGGING})
source_group("Vang/Utility/Player" FILES ${Vang_UTILITY_PLAYER})
source_group("Vang/Window" FILES ${Vang_WINDOW})
source_group("Vang/Window/WindowGLFW" FILES ${Vang_WINDOW_WINDOWGLFW})
source_group("Vang/GraphicsAPI/Generic" FILES ${Vang_GRAPHICSAPI})
source_group("Vang/GraphicsAPI/Generic/Shader" FILES ${Vang_GRAPHICSAPI_SHADER})
source_group("Vang/GraphicsAPI/Generic/ShaderProgram" FILES ${Vang_GRAPHICSAPI_SHADERPROGRAM})
source_group("Vang/GraphicsAPI/GraphicsVulkan" FILES ${Vang_GRAPHICSAPI_GRAPHICSVULKAN})
source_group("Vang/GraphicsAPI/GraphicsVulkan/VulkanHelpers" FILES ${Vang_GRAPHICSAPI_GRAPHICSVULKAN_VULKANHELPERS})
source_group("Vang/GraphicsAPI/GraphicsOpenGL" FILES ${Vang_GRAPHICSAPI_GRAPHICSOPENGL})
source_group("Vang/GraphicsAPI/GraphicsOpenGL/Shader" FILES ${Vang_GRAPHICSAPI_GRAPHICSOPENGL_SHADER})


# WINDOW API'S:
#   VANG_WINDOW_GLFW

# GRAPHICS API'S:
#   VANG_GRAPHICSAPI_VULKAN
#     VANG_GRAPHICSAPI_VULKAN_VALIDATION_LAYERS
#   VANG_GRAPHICSAPI_OPENGL

# OTHER:
#   VANG_DEBUG - Log warning, info, and debug
target_compile_definitions(Vang
	PRIVATE
		VANG_WINDOW_GLFW
		VANG_GRAPHICSAPI_OPENGL
		VANG_DEBUG
)

target_link_libraries(Vang
	PRIVATE
		glad::glad
		glfw
		Vulkan::Vulkan
	PUBLIC
		imgui::imgui
		glm::glm
		spdlog::spdlog
)

target_include_directories(Vang
	PUBLIC
		"./src"
)

target_precompile_headers(Vang
	PUBLIC
		"./src/VangPCH.h"
)