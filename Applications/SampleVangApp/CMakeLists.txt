include(CMakeFiles.cmake)

add_executable(SampleVangApp ${SampleVangApp_Files})

add_dependencies(SampleVangApp Vang)

target_link_libraries(SampleVangApp PRIVATE Vang)