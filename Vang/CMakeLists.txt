include(CMakeFiles.cmake)

add_library(Vang STATIC ${Vang_FILES})

if (BAKE_SHADERS)
    add_custom_command(
		TARGET Vang
		PRE_BUILD
		COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_SOURCE_DIR}/CmakeScripts/bakeShaders.py" "${CMAKE_CURRENT_SOURCE_DIR}/shaders" "${CMAKE_CURRENT_BINARY_DIR}/shaders"
	)

	# Generate Files for CMake Generate Step
	file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/shaders/bakedShaders.h" CONTENT "")
	file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/shaders/bakedShaders.cpp" CONTENT "")

	target_sources(Vang PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/shaders/bakedShaders.h")
	target_sources(Vang PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/shaders/bakedShaders.cpp")
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

# OTHER:
#	VANG_BLOCK_LOGGING_COUT - Block logging cout messages (unit_tests)
#	VANG_REMOVE_DEBUG_MESSAGES - Remove debugging messages
target_compile_definitions(Vang
	PUBLIC
		VANG_WINDOW_GLFW
		VANG_GRAPHICSAPI_OPENGL
)

if(BUILD_PACKAGE)
	target_compile_definitions(Vang
		PRIVATE
			VANG_REMOVE_DEBUG_MESSAGES	
	)
endif()

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