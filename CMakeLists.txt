cmake_minimum_required(VERSION 2.8)
project(SEYCHELLES)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

set(SEYCHELLES_SRC 
    seychelles.cpp
    libedit.cpp
    command_registry.cpp
    commands.cpp
    insults.cpp
    ssh.cpp
    log.cpp
)

add_definitions(-DSEYCHELLES_DEBUG)

add_executable(seychelles ${SEYCHELLES_SRC})
target_link_libraries(seychelles edit curses)
