add_executable(stevensStringLib_tests
    unit/string_validation_test.cpp
    unit/string_manipulation_test.cpp
    unit/string_searching_test.cpp
    unit/string_conversion_test.cpp
    unit/property_based_test.cpp
)

target_link_libraries(stevensStringLib_tests
    PRIVATE
        stevensStringLib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(stevensStringLib_tests)
