cmake_minimum_required(VERSION 3.7)
project(PinballController)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")


find_package(SFML 2 REQUIRED  audio graphics window system)
find_package(Boost REQUIRED COMPONENTS system)

include_directories(${SFML_INCLUDE_DIR} include ${Boost_INCLUDE_DIRS})

add_executable(PinballController main.cpp src/PinballScreenRenderer.cpp)

target_link_libraries(PinballController ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${Boost_LIBRARIES} -lpthread)
