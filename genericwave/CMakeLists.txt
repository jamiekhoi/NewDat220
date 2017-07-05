cmake_minimum_required(VERSION 3.6)
project(genericwave)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp state.h gamemachine.cpp gamemachine.h TestState.cpp TestState.h map.cpp map.h
        layer.cpp layer.h object.cpp object.h sprite.cpp sprite.h Player.cpp Player.h Weapon.h Pistol.cpp Pistol.h CollisionTester.cpp CollisionTester.h Obstacle.cpp Obstacle.h Bullet.cpp Bullet.h Enemy.cpp Enemy.h)
add_executable(genericwave ${SOURCE_FILES})

target_link_libraries(genericwave jsoncpp sfml-audio sfml-graphics sfml-window sfml-system)