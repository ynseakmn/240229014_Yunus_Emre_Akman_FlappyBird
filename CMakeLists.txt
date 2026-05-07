cmake_minimum_required(VERSION 3.10)
project(FlappyBird)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML bulma
find_package(SFML COMPONENTS Graphics Window System REQUIRED)

# Executable oluştur
add_executable(FlappyBird 
    main.cpp
    bird.cpp
    oyun.cpp
)

# SFML'i linke et
target_link_libraries(FlappyBird PRIVATE SFML::Graphics SFML::Window SFML::System)