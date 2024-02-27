include(CMakeFiles.cmake)

add_executable(TerrainGenerationTestApp ${TerrainGenerationTestApp_Files})

add_dependencies(TerrainGenerationTestApp Vang)

target_link_libraries(TerrainGenerationTestApp PRIVATE Vang)