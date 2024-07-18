include(CMakeFiles.cmake)

add_executable(SampleVangApp ${SampleVangApp_Files})

add_dependencies(SampleVangApp Vang)

target_link_libraries(SampleVangApp PRIVATE Vang)

# Remove Terminal Window On Startup
if (BUILD_PACKAGE)
    if (WIN32)
        set(SUBSYSTEM_LINKER_OPTIONS "/SUBSYSTEM:WINDOWS" "/ENTRY:mainCRTStartup")
    else()
        set(SUBSYSTEM_LINKER_OPTIONS "-mwindows")
    endif()
endif()

target_link_options(SampleVangApp PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})