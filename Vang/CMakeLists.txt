include(CMakeFiles.cmake)

add_library(Vang STATIC ${Vang_FILES})

# WINDOW API'S:
#   VANG_WINDOW_GLFW

# GRAPHICS API'S:
#   VANG_GRAPHICSAPI_VULKAN
#     VANG_GRAPHICSAPI_VULKAN_VALIDATION_LAYERS
#   VANG_GRAPHICSAPI_OPENGL

# OTHER:
#   VANG_DEBUG - Log warning, info, and debug
#	VANG_BLOCK_LOGGING_COUT - Block logging cout messages (unit_tests)
target_compile_definitions(Vang
	PRIVATE
		VANG_WINDOW_GLFW
		VANG_GRAPHICSAPI_OPENGL
		VANG_DEBUG
)

target_link_libraries(Vang
	PUBLIC
		glad
		glfw
		glm::glm
)

target_include_directories(Vang
	PUBLIC
		"./src"
)

target_compile_features(Vang PUBLIC cxx_std_20)

target_compile_definitions(Vang PRIVATE VANG_SHADERS_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/shaders" )

target_precompile_headers(Vang
	PUBLIC
		"./src/VangPCH.h"
)

add_subdirectory("tests")