cmake_minimum_required(VERSION 3.10...3.50)
project(DelMesh VERSION 0.2)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build unit tests" ON)


#Gathering source files
file(GLOB_RECURSE LIB_SOURCES "src/DelMesh/*.cpp")
file(GLOB_RECURSE LIB_HEADERS "src/DelMesh/*.h" "src/DelMesh*.hpp")

list(FILTER LIB_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

# Creating Library Target
add_library(DelMesh ${LIB_SOURCES} ${LIB_HEADERS})

target_compile_options(DelMesh  PUBLIC -Wno-deprecated-copy)

#Compiling main if exists
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    add_executable(DelMeshDemo src/main.cpp)
    target_link_libraries(DelMeshDemo DelMesh)
    set_target_properties(DelMeshDemo PROPERTIES OUTPUT_NAME delmesh)
endif()

#Setting Include Directories
target_include_directories(DelMesh
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DelMesh
)


if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/Eigen")
    target_include_directories(DelMesh PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/Eigen")
else()
    find_package(Eigen3 REQUIRED)
    target_link_libraries(DelMesh PUBLIC Eigen3::Eigen)
endif()

target_compile_options(DelMesh PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

find_package(gflags REQUIRED)
target_link_libraries(DelMesh PUBLIC gflags)

set_target_properties(DelMesh PROPERTIES POSITION_INDEPENDENT_CODE ON)


if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS DelMesh
    EXPORT DelMeshTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES ${LIB_HEADERS} DESTINATION include/DelMesh)

install(EXPORT DelMeshTargets
    FILE DelMeshTargets.cmake
    NAMESPACE DelMesh::
    DESTINATION lib/cmake/DelMesh
)

# Create config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "DelMeshConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/DelMeshConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/DelMeshConfig.cmake"
    INSTALL_DESTINATION lib/cmake/DelMesh
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/DelMeshConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/DelMeshConfigVersion.cmake"
    DESTINATION lib/cmake/DelMesh
) 
