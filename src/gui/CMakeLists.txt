#
# Created by XiaoLey on 2023/05/28.
#

include(Add_wxWidgets)

add_executable(rescue_gui main.cpp)
add_dependencies(rescue_gui rescue)

target_sources(
  rescue_gui PRIVATE
  configset/configset.cpp configset/configset_ui.cpp
  mainwin/mainwin.cpp mainwin/mainwin_ui.cpp
  res/resources.c
)

target_include_directories(
  rescue_gui PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(rescue_gui PRIVATE wx::core wx::base rapidjson)

set_target_properties(
  rescue_gui PROPERTIES
  OUTPUT_NAME "rescue-gui"
)
