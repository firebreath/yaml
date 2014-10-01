
set (YAML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/yamlcpp)

add_subdirectory(${YAML_DIR})

include_directories(${YAML_DIR} ${FB_SCRIPTINGCORE_SOURCE_DIR})

file (GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    [^.]*.cpp
    [^.]*.h
    )

add_library(yaml ${SOURCES})

append_firebreath_link_library(yaml-cpp)
append_firebreath_link_library(yaml)
append_firebreath_include_dir(${YAML_DIR}/include)
append_firebreath_include_dir(${CMAKE_CURRENT_SOURCE_DIR})
