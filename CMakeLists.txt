cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.11)
set(CMAKE_OSX_SYSROOT /)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)

add_compile_options(-Wall)
# mostly for puredata sources:
#add_compile_options(-Wno-unused-parameter)

if(POLICY CMP0074)
    #policy for <PackageName>_ROOT variables
    cmake_policy(SET CMP0074 NEW)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/compactlib/cmake)

project(pdinstance_tester)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/pd_headers")

add_library(pdinstance_tester SHARED src/instance_tester.cpp)

if (NOT WIN32)
set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
endif()

set_target_properties( pdinstance_tester
        PROPERTIES

        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/package"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/package"
)


add_custom_command(
TARGET pdinstance_tester 
PRE_BUILD
                     
COMMAND ${CMAKE_COMMAND} -E
                         copy 
${CMAKE_SOURCE_DIR}/help/pdinstance_tester-help.pd 
${CMAKE_SOURCE_DIR}/package/pdinstance_tester-help.pd
)

if (NOT WIN32)
set_target_properties(pdinstance_tester PROPERTIES SUFFIX ".pd_darwin")
endif()

set_target_properties(pdinstance_tester PROPERTIES PREFIX "")


