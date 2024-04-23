set(VANG_UNIT_TESTS_SOURCES
    "src/BlueprintContainerUnitTests.cpp"
    "src/ChunkUnitTests.cpp"
)

add_executable(Vang_unit_tests ${VANG_UNIT_TESTS_SOURCES})

target_link_libraries(Vang_unit_tests PRIVATE Vang Catch2::Catch2WithMain)

target_compile_features(Vang_unit_tests PRIVATE cxx_std_20)

enable_testing()
add_test(NAME Vang_unit_tests COMMAND $<TARGET_FILE:Vang_unit_tests>)