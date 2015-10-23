
cmake_minimum_required (VERSION 2.8)

set (PROJECT_NAME oda-examples)
project (${PROJECT_NAME} C CXX)

set (IMPORT_DIR ${CMAKE_INSTALL_PREFIX}
     CACHE FILEPATH "Where to look for exported target scripts.")

set (CMAKE_C_FLAGS_DEBUG "-O0 -g")
set (CMAKE_C_FLAGS_RELEASE "-O3")

# Include exported cmake spec from liboda
# The targets is named "oda"
include (${IMPORT_DIR}/cmake/liboda.cmake)

# Custom target: assets
add_custom_target (
  assets
  COMMAND cmake -E copy patches/derp.ogg ${CMAKE_BINARY_DIR}
  COMMAND cmake -E copy patches/2_pianoogg.ogg ${CMAKE_BINARY_DIR}
  COMMAND cmake -E copy patches/4_hihatclosedogg.ogg ${CMAKE_BINARY_DIR}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Building assets"
)

add_subdirectory (src)

