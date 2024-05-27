cmake_minimum_required(VERSION 3.14)
project(Arkanoid)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(Arkanoid main.cpp
        Arkanid.cpp
        Meteor.cpp
        Base_object.cpp
        Alien.cpp
        Gun.cpp
        Boss_alien.cpp
        Gun_boss.cpp
        Gun_alien.cpp
)


if(WIN32)
    set(SFML_ROOT "C:\\SFML-2.5.1")
    set(SFML_STATIC_LIBRARIES TRUE)
else()
    include_directories(/usr/local/include)
endif()

# Поиск компонентов библиотеки
find_package(SFML 2.5.1 COMPONENTS graphics window system audio REQUIRED)

if(SFML_FOUND)
    # Добавление headers
    target_include_directories(Arkanoid PRIVATE ${SFML_INCLUDE_DIR})
    # Линковка библиотек
    target_link_libraries(Arkanoid PRIVATE m sfml-graphics sfml-window sfml-system sfml-audio)
endif()