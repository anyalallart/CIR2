cmake_minimum_required(VERSION 3.23)
project(BIM_Client)

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

add_executable(BIM_Client ../classes/socket/tsQueue.h ../classes/socket/Message.h ../classes/socket/Connection.h ../classes/socket/Client.h ../classes/socket/Server.h
        Design/main.cpp Design/main.h Design/accueil.cpp Design/accueil.h Design/connexion.cpp Design/connexion.h Design/crea.cpp Design/crea.h Design/info_compt.cpp Design/info_compt.h
        Design/virement.cpp Design/virement.h Design/include.h)
#add_executable(BIM_Client main.cpp ../classes/socket/tsQueue.h ../classes/socket/Message.h ../classes/socket/Connection.h ../classes/socket/Client.h ../classes/socket/Server.h)

set_property(TARGET BIM_Client PROPERTY CXX_STANDARD 17)

if(MSVC)
    set_target_properties(BIM_Client PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS)
    #set_target_properties(BIM_Client PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)

    set_property(TARGET BIM_Client PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)

target_link_libraries(BIM_Client PRIVATE ${Boost_LIBRARIES} ${wxWidgets_LIBRARIES} unofficial::sqlite3::sqlite3)
target_include_directories(BIM_Client PRIVATE ${Boost_INCLUDE_DIRS} wx::core wx::base wx::net)