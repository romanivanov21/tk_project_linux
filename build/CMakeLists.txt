cmake_minimum_required (VERSION 2.6)

set (PROJECT tk_client)

set (HEADRES boost/asio.hpp network_client.h ../shared/gost_include.h)

set (SOURCES ../main.cpp ../network_client/network_client.cpp)

set (LIBRARIES )

set (BOOST_COMPONENTS system)

set (Boost_USE_STATIC_LIBS ON)

set (Boost_USE_MULTITHREADED ON)

set (GOST_LIBS crypt_gost_28147_89_API)

project (${PROJECT})

include_directories (../)

find_package (Threads)

find_package (Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

foreach (LIBRARY ${LIBRARIES})
	add_subdirectory (../${LIBRARY}/build bin/${LIBRARY})
endforeach ()

add_subdirectory (../crypt_gost_28147-89/build bin/${GOST_LIBS})

if (MSVC)
	add_definitions (/W4)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	add_definitions (-Wall -pedantic)
else ()
	message ("Unknown compiler")
endif ()

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

target_link_libraries (${PROJECT} ${LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${GOST_LIBS} ${Boost_LIBRARIES})

enable_testing ()
