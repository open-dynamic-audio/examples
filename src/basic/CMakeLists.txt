
# Source files
set (VORPAL_EXAMPLES_BASIC_SRC main.cxx)

# Define our program target
add_executable (basic ${VORPAL_EXAMPLES_BASIC_SRC})

# Link with liboda
target_link_libraries (basic LINK_PUBLIC oda)

# Set a few properties
#  - Use C++11
#  - Output binary to <build dir>/bin
set_target_properties (
  basic PROPERTIES
  COMPILE_FLAGS "-std=c++11"
  COMPILE_DEFINITIONS
  VORPAL_PATCHES_PATH="${IMPORT_DIR}/patches"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_dependencies (basic assets)
