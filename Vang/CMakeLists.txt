include(CMakeFiles.cmake)

add_library(Vang STATIC ${Vang_FILES})

if (BAKE_SHADERS)
    add_custom_command(
		TARGET Vang
		PRE_BUILD
		COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_SOURCE_DIR}/CmakeScripts/bakeShaders.py" "${CMAKE_CURRENT_SOURCE_DIR}/shaders" "${CMAKE_CURRENT_BINARY_DIR}/shaders"
	)
	file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/shaders/bakedShaders.h" CONTENT "")
	target_sources(Vang PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/shaders/bakedShaders.h")
	target_compile_definitions(Vang PRIVATE VANG_BAKED_SHADERS)
	target_compile_definitions(Vang PRIVATE VANG_SHADERS="${CMAKE_CURRENT_BINARY_DIR}/shaders/bakedShaders.h" )
else(BAKE_SHADERS)
	target_compile_definitions(Vang PRIVATE VANG_SHADERS_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/shaders" )
endif (BAKE_SHADERS)

# WINDOW API'S:
#   VANG_WINDOW_GLFW

# GRAPHICS API'S:
#   VANG_GRAPHICSAPI_VULKAN
#     VANG_GRAPHICSAPI_VULKAN_VALIDATION_LAYERS
#   VANG_GRAPHICSAPI_OPENGL

# RENDERING METHODS:
#	VANG_RENDERING_PLANEASSISTED
#	VANG_RENDERING_CUBOID
#	VANG_RENDERING_OCTREE

# OTHER:
#	VANG_BLOCK_LOGGING_COUT - Block logging cout messages (unit_tests)
target_compile_definitions(Vang
	PRIVATE
		VANG_WINDOW_GLFW
		VANG_GRAPHICSAPI_OPENGL
		VANG_RENDERING_CUBOID
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

target_precompile_headers(Vang
	PUBLIC
		"./src/VangPCH.h"
)

add_subdirectory("tests")