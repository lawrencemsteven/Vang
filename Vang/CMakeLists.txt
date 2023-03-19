include(CMakeFiles.cmake)

add_library(Vang STATIC ${Vang_FILES})

target_compile_features(Vang PUBLIC cxx_std_20)

source_group("Vang" FILES ${Vang_Vang})
source_group("Vang/Utility/Logging" FILES ${Vang_UTILITY_LOGGING})

target_compile_definitions(Vang
	PRIVATE
		VANG_DEBUG
		GLFW_INCLUDE_NONE
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