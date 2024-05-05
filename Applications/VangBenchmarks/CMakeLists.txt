include(CMakeFiles.cmake)

add_executable(VangBenchmarks ${VangBenchmarks_Files})

add_dependencies(VangBenchmarks Vang)

target_link_libraries(VangBenchmarks PRIVATE Vang)