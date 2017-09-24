cmake_minimum_required(VERSION 3.6)
project(genericwave)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp state.h gamemachine.cpp gamemachine.h TestState.cpp TestState.h map.cpp map.h
        layer.cpp layer.h object.cpp object.h sprite.cpp sprite.h Player.cpp Player.h Weapons/Weapon.h Weapons/Pistol.cpp Weapons/Pistol.h CollisionTester.cpp CollisionTester.h Obstacle.cpp Obstacle.h Bullet.cpp Bullet.h Enemy.cpp Enemy.h Pickup.cpp Pickup.h Weapons/AutomaticWeapon.cpp Weapons/AutomaticWeapon.h MainMenuState.cpp MainMenuState.h)
add_executable(genericwave ${SOURCE_FILES})

target_link_libraries(genericwave jsoncpp sfml-audio sfml-graphics sfml-window sfml-system)