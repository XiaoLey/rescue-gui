#
# Created by XiaoLey on 2023/05/28.
#

set(RAPIDJSON_BUILD_TESTS OFF)
set(RAPIDJSON_BUILD_DOC OFF)
set(RAPIDJSON_BUILD_EXAMPLES OFF)
set(RAPIDJSON_BUILD_THIRDPARTY_GTEST OFF)
add_subdirectory(rapidjson)
add_library(rapidjson INTERFACE IMPORTED)
set_property(TARGET rapidjson PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/include)

add_subdirectory(rescue)
add_subdirectory(gui)
