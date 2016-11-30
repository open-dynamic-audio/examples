
# Source files
set (VORPAL_EXAMPLES_HELLO_SRC main.cxx)

# Define our program target
add_executable (hello ${VORPAL_EXAMPLES_HELLO_SRC})

# Link with libvorpal
target_link_libraries (hello LINK_PUBLIC vorpal)

# Set a few properties
#  - Use C++11
#  - Output binary to <build dir>/bin
set_target_properties (
  hello PROPERTIES
  COMPILE_FLAGS "-std=c++11"
  COMPILE_DEFINITIONS
  VORPAL_PATCHES_PATH="${IMPORT_DIR}/patches"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_dependencies (hello assets)
