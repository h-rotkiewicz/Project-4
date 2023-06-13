cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS ON)
set(DEBUG_FLAGS "-g -O0 -Wall -Wextra -Wpedantic -Werror")

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
add_executable(MyProject ${SOURCES})

find_package(X11 REQUIRED)
if(X11_FOUND)
  include_directories(${X11_INCLUDE_DIR})
  target_link_libraries(MyProject ${X11_LIBRARIES})
endif()

find_library(XEXT_LIBRARY Xext)
if(XEXT_LIBRARY)
  target_link_libraries(MyProject ${XEXT_LIBRARY})
endif()
