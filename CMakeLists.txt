# minimun requirements
# my cmake cmake version 3.14.5
cmake_minimum_required(VERSION 3.9.4)
#project name
project(ott)

# set cmake variables.
set( OTT_FLAGS )
if(DEFINED ENV{OTT_ROOT})
    message("OTT_ROOT is well defined")
    set( OTT_FLAGS $ENV{OTT_ROOT})
endif()

message("OTT_ROOT : D${OTT_ROOT}")
if(OTT_ROOT)
    message("D${OTT_ROOT} is well defined")
    set( OTT_FLAGS ${OTT_ROOT})
endif()

#execute_process(COMMAND "pwd > OTT_FLAGS")

message("Starting building ott platform")
message("OTT_FLAGS : ${OTT_FLAGS}")
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
if (MSVC)
    message("no supported for now")
else()
    set (THREADS_PREFER_PTHREAD_FLAG ON)
    find_package (Threads)
    link_libraries(Threads::Threads)


    set( CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-missing-braces -Wmissing-field-initializers -fcoroutines ")

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wrange-loop-analysis")
    endif ()
endif()

#-------------------------------------------------------------------------------
#
# OpenSSL
#
#-------------------------------------------------------------------------------

#if (APPLE AND NOT DEFINED ENV{OPENSSL_ROOT_DIR})
#  find_program(HOMEBREW brew)
#  if (NOT HOMEBREW STREQUAL "HOMEBREW-NOTFOUND")
#    execute_process(COMMAND brew --prefix openssl
#      OUTPUT_VARIABLE OPENSSL_ROOT_DIR
#      OUTPUT_STRIP_TRAILING_WHITESPACE)
#  endif()
#endif()

#find_package(OpenSSL)
#if (NOT MSVC)
#    link_libraries(${OPENSSL_LIBRARIES})
#endif()
#message("OPEBSSL_FOUND FLAGS is ${OPENSSL_FOUND}")
#if (OPENSSL_FOUND)
#    include_directories (${OPENSSL_INCLUDE_DIR})
#endif()

set( BOOST_ROOT ${OTT_FLAGS}/third_parties/boost/boost/build)
message("${BOOST_ROOT}")

set( Boost_INCLUDE_DIRS ${BOOST_ROOT}/include )
set( Boost_LIB_DIRS ${BOOST_ROOT}/lib)

#google test
set(GTEST_ROOT ${OTT_FLAGS}/third_parties/googletest/libs)

#
#find_package(Boost REQUIRED)
add_subdirectory(lib)


# add new feature
