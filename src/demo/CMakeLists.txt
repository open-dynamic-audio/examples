
add_custom_target (
  demo ALL
  COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/demo
  COMMAND cmake -E copy main.lua ${CMAKE_BINARY_DIR}/demo
  COMMAND cmake -E copy conf.lua ${CMAKE_BINARY_DIR}/demo
  COMMAND cmake -E copy defs.lua ${CMAKE_BINARY_DIR}/demo
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/defs.in.lua
  ${CMAKE_CURRENT_SOURCE_DIR}/defs.lua
)

