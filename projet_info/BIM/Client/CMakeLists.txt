cmake_minimum_required(VERSION 3.23)
project(BIM_Client)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_RELEASE_LIBS ON)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(Boost_USE_STATIC_RUNTIME ON)
    set(Boost_DIR "C:/tools/Boost/lib/cmake/Boost-1.80.0")

    set(wxWidgets_ROOT_DIR  "C:/tools/wxWidgets")
    set(CMAKE_PREFIX_PATH  "C:/tools/wxWidgets")
    add_compile_options($<$<CONFIG:Release>:/MT> # Runtime library: Multi-threaded
            $<$<CONFIG:Debug>:/MTd> # Runtime library: Multi-threaded Debug
            )
elseif(MSVC)
        set(Boost_DIR C:/tools/Boost/lib/cmake/Boost-1.80.0)
endif (MSVC)

find_package(Boost 1.80.0 COMPONENTS json serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

add_executable(BIM_Client main.cpp ../classes/Compte.cpp ../classes/Compte.h ../classes/Client.cpp ../classes/Client.h ../classes/socket/tsQueue.h ../classes/socket/Message.h ../classes/socket/Connection.h ../classes/socket/Client.h ../classes/socket/Server.h ../classes/json/json.h)

set_property(TARGET BIM_Client PROPERTY CXX_STANDARD 17)

target_link_libraries (BIM_Client LINK_PUBLIC ${Boost_LIBRARIES} ${wxWidgets_LIBRARIES})



