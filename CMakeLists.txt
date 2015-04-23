
cmake_minimum_required (VERSION 2.8)

set (PROJECT_NAME oda-examples)
project (${PROJECT_NAME} C CXX)

find_package (OpenAL REQUIRED)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../liboda/install/cmake)
include (../liboda/install/cmake/liboda.cmake)

set (PROJECT_SRC src/main.cxx)

get_target_property (ODA_INCLUDE_DIR oda INTERFACE_INCLUDE_DIRECTORIES)
message (STATUS "Liboda include dir: ${ODA_INCLUDE_DIR}")
include_directories (${ODA_INCLUDE_DIR})

include_directories (${OPENAL_INCLUDE_DIR})
include_directories (src)

add_executable (example ${PROJECT_SRC})

target_link_libraries (example LINK_PUBLIC oda ${OPENAL_LIBRARY})

set_target_properties (
  example PROPERTIES
  COMPILE_FLAGS "-std=c++11"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  INCLUDE_DIRECTORIES $<TARGET_PROPERTY:oda,INTERFACE_INCLUDE_DIRECTORIES> 
)

