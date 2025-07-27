include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0


)

FetchContent_MakeAvailable(googletest)


# Collect c++ source giles recursively
file(GLOB_RECURSE CXX_FILES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
add_executable(unit_tests ${CXX_FILES})

# Link GoogleTest Libraries
target_link_libraries(unit_tests
    PRIVATE
    gtest_main
    ${PROJECT_NAME} #link to the main project library
)

# include directories (including where GoogleTest is built)
target_include_directories(unit_tests PRIVATE ${gtest_SOURCE_DIR}/include)

# Add include directores for tests to find headers
target_include_directories(unit_tests PRIVATE ${PROJECT_SOURCE_DIR}/src)

# Enable testing and discover tests
# Discover and run tests
include(GoogleTest)
gtest_discover_tests(unit_tests)