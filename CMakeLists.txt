cmake_minimum_required(VERSION 3.14)
project(Arkanoid LANGUAGES CXX)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 17)
add_executable(main main.cpp
        main.cpp)
target_link_libraries(Arkanoid sfml-graphics)