cmake_minimum_required(VERSION 3.16)
project(EchoRay LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.0
)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(SFML glm googletest)

file(GLOB_RECURSE SOURCES
        src/*.h
        src/*.cpp)

file(GLOB_RECURSE TEST_SOURCES
        src/*.h
        src/*.cpp)

list(FILTER TEST_SOURCES EXCLUDE REGEX "main.cpp")

file(GLOB_RECURSE TESTS
        tests/*.h
        tests/*.cpp
        tests/*.cc)

add_executable(EchoRay ${SOURCES})
target_link_libraries(EchoRay PRIVATE sfml-graphics sfml-window glm)
target_compile_features(EchoRay PRIVATE cxx_std_23)

enable_testing()
add_executable(EchoRayTests ${TESTS} ${TEST_SOURCES})
target_link_libraries(EchoRayTests PRIVATE sfml-graphics sfml-window glm gtest_main)

include(GoogleTest)
gtest_discover_tests(EchoRayTests)

install(TARGETS EchoRay)
