cmake_minimum_required(VERSION 3.14)
project(Arkanoid)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp
        Arkanoid.h
        Arkanid.cpp
        Meteor.cpp
        Meteor.h
        Base_object.h
        Base_object.cpp
        Alien.cpp
        Alien.h)
add_executable(Arkanoid ${SOURCE_FILES})


if(WIN32)
    set(SFML_ROOT "C:\\SFML-2.6.1")
    set(SFML_STATIC_LIBRARIES TRUE)
else()
    include_directories(/usr/local/include)
endif()

# Поиск компонентов библиотеки
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

if(SFML_FOUND)
    # Добавление headers
    target_include_directories(Arkanoid PRIVATE ${SFML_INCLUDE_DIR})
    # Линковка библиотек
    target_link_libraries(Arkanoid PRIVATE m sfml-graphics sfml-window sfml-system)
endif()