include(CMakeFiles.cmake)

add_executable(VangApp ${VangApp_FILES})

add_dependencies(VangApp Vang)

target_link_libraries(VangApp PRIVATE Vang)

target_compile_features(VangApp PUBLIC cxx_std_20)

target_include_directories(VangApp
	PUBLIC
		"src"
)

# Temporary for testing
target_link_libraries(VangApp
	PRIVATE
		glad::glad
		glfw
		Vulkan::Vulkan
	PUBLIC
		glm::glm
)