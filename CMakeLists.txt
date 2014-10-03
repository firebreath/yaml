
set (YAML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/yamlcpp)

if (NOT BOOST_ROOT)
    set(BOOST_ROOT ${FB_BOOST_SOURCE_DIR})
endif()
option(YAML_CPP_BUILD_TOOLS "Tests and stuff for yaml-cpp" OFF)

add_subdirectory(${YAML_DIR})

include_directories(
    ${YAML_DIR}/include
    ${FB_SCRIPTINGCORE_SOURCE_DIR}
    ${FB_CONFIG_DIR})

file (GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    yaml*.cpp
    yaml*.h
    )

if (YAML_SUPPORT_CONFIG)
    add_firebreath_library(ConfigManager)
    file (GLOB CFGSOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        Config*.cpp
        Config*.h
        )
    include_directories(${FBLIB_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
    set(SOURCES ${SOURCES} ${CFGSOURCES})
endif()

add_library(yaml ${SOURCES})

append_firebreath_link_library(yaml-cpp)
append_firebreath_link_library(yaml)
append_firebreath_include_dir(${YAML_DIR}/include)
append_firebreath_include_dir(${CMAKE_CURRENT_SOURCE_DIR})

