cmake_minimum_required(VERSION 3.23)
project(TestBoost)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_RELEASE_LIBS ON)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(Boost_USE_STATIC_RUNTIME ON)
    set(Boost_DIR "lib/Boost/lib/cmake/Boost-1.80.0")
elseif(MSVC)
    set(Boost_DIR lib/Boost/lib/cmake/Boost-1.80.0)
endif (MSVC)

find_package(Boost 1.80.0 COMPONENTS json serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(src main.cpp)
add_executable(TestBoost ${src})
target_link_libraries (TestBoost ${Boost_LIBRARIES})
