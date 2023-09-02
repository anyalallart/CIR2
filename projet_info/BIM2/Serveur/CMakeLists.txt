cmake_minimum_required(VERSION 3.23)
project(BIM_Serveur)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_RELEASE_LIBS ON)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(Boost_USE_STATIC_RUNTIME ON)

    add_compile_options($<$<CONFIG:Release>:/MT>     # Runtime library: Multi-threaded
            $<$<CONFIG:Debug>:/MTd> # Runtime library: Multi-threaded Debug
            )
endif (MSVC)

find_package(Boost REQUIRED COMPONENTS json serialization)
find_package(wxWidgets CONFIG REQUIRED COMPONENTS core base net)
find_package(unofficial-sqlite3 REQUIRED)

#add_executable(BIM_Serveur main.cpp ../classes/socket/tsQueue.h ../classes/socket/Message.h ../classes/socket/Connection.h ../classes/socket/Client.h ../classes/socket/Server.h ../classes/database/DB.h)
add_executable(BIM_Serveur Design/banque.cpp Design/banque.h ../classes/socket/tsQueue.h ../classes/socket/Message.h ../classes/socket/Connection.h ../classes/socket/Client.h ../classes/socket/Server.h ../classes/database/DB.h)

if(MSVC)
    set_target_properties(BIM_Serveur PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS)
    #set_target_properties(BIM_Serveur PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)

    set_property(TARGET BIM_Serveur PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)


set_property(TARGET BIM_Serveur PROPERTY CXX_STANDARD 17)

target_link_libraries(BIM_Serveur PRIVATE ${Boost_LIBRARIES} ${wxWidgets_LIBRARIES} unofficial::sqlite3::sqlite3)
target_include_directories(BIM_Serveur PRIVATE ${Boost_INCLUDE_DIRS} wx::core wx::base wx::net)