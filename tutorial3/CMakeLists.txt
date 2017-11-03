# Our minimum cmake list

# Setup Project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(tutorial3)

# Find Geant4 and activate ALL UI and vis drivers by default
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
option(ui_all ON)
option(vis_all ON)
MESSAGE( STATUS "Geant4_qt_FOUND: " ${Geant4_qt_FOUND} )
MESSAGE( STATUS "Geant4_vis_opengl_x11_FOUND: " ${Geant4_vis_opengl_x11_FOUND} )

# Setup include directories
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Locate the source and header files
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Add exec and links the libraries
add_executable(tutorial3 tutorial3.cpp ${sources} ${headers})
target_link_libraries(tutorial3 ${Geant4_LIBRARIES})

# if you want to copy scripts over uncomment this section
 set(TUTORIAL_SCRIPTS
   init_vis.mac
   run.mac
   vis.mac
   )
# 
foreach(_script ${TUTORIAL_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

# Install exec's to bin directory under CMAKE_INSTALL_PREFIX
install(TARGETS tutorial3 DESTINATION bin)
