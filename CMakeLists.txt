cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(Visualizer)
SET(VTK_DIR /path/to/VTK6.0.0)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(Visualizer Visualizer)

if(VTK_LIBRARIES)
  target_link_libraries(Visualizer ${VTK_LIBRARIES})
else()
  target_link_libraries(Visualizer vtkHybrid)
endif()

