
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

# Source files
set (PROJECT_SRC src/main.cxx)

# Paths used by #include <...>
include_directories (src)

# Define our program target
add_executable (example ${PROJECT_SRC})

# Link with liboda
target_link_libraries (example LINK_PUBLIC oda)

# Set a few properties
#  - Use C++11
#  - Output binary to <build dir>/bin
set_target_properties (
  example PROPERTIES
  COMPILE_FLAGS "-std=c++11"
  COMPILE_DEFINITIONS
  ODA_PATCHES_PATH="${CMAKE_SOURCE_DIR}/${IMPORT_DIR}/patches"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Custom target: assets
add_custom_target (
  assets
  COMMAND cmake -E copy patches/derp.ogg ${CMAKE_BINARY_DIR}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Building assets"
)

add_dependencies (example assets)

