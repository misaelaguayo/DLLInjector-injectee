cmake_minimum_required(VERSION 3.0)

project(makefile_dll)

add_definitions(-D_WIN32_WINNT=0x0502)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" -m32)
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}" -m32)

set(dll-injector-src
	"src/injector.cpp"
)

set(dll-injector_lib
	"psapi"
)

add_executable(dll-injector ${dll-injector_src})
target_link_libraries(dll-injector ${dll-injector_lib})

set(injected_src
	"src/dll/dll.cpp"
)

add_library(injected MODULE ${injected_src})