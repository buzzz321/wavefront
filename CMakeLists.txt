# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

cmake_minimum_required(VERSION 3.5)
# set(CMAKE_C_COMPILER "clang")
#set(CMAKE_CXX_COMPILER "clang++")

project(wfreader)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux") 
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_SOURCE_DIR}/cmake/")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
include_directories(${CMAKE_SOURCE_DIR}/glm)
    link_directories(${CMAKE_SOURCE_DIR}/glm)
    
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_SOURCE_DIR}/glm/ ) 
    message(STATUS "---> ${CMAKE_MODULE_PATH}")
endif()


set (SRCS
    main.cc
    wavefrontreader.cc
)

add_executable(${CMAKE_PROJECT_NAME} ${SRCS})
target_link_libraries(${CMAKE_PROJECT_NAME} )

