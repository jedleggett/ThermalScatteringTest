#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(thermalScatteringTest)

#----------------------------------------------------------------------------
# check MPI package...
#find_package(MPI REQUIRED)
# modify these var. if needed
#set(CMAKE_CXX_COMPILER mpicxx)
#set(CMAKE_CXX_INCLUDE_PATH )

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

# Find extra packages directory 
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Geant4_DIR}/cmake/Modules/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}")

#----------------------------------------------------------------------------
# Add G4mpi library
#
#include(${Geant4_DIR}/../G4mpi-targets.cmake)
#SET(Geant4_LIBRARIES ${Geant4_LIBRARIES} G4mpi)

#----------------------------------------------------------------------------
#Setup HepMC

#find_package (HepMC REQUIRED)
# MESSAGE(STATUS "LIBS " ${LIBS} )
#if (HepMC_FOUND)
# include_directories(${HepMC_INCLUDE_DIRS})
# set(LIBS ${LIBS} ${HepMC_LIBRARIES})
#endif (HepMC_FOUND)

#  include_directories(${HepMC_INCLUDE_DIRS})
#  set(LIBS ${LIBS} HepMC)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# Setup include directory for this project
# NB: headers are included so they will show up in IDEs
#
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/*.mac)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIR})

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(thermalScatteringTest thermalScatteringTest.cc ${sources} ${headers})
set(LIBS ${LIBS} ${Geant4_LIBRARIES})
target_link_libraries(thermalScatteringTest ${LIBS} )

set(THERMALSCATTERINGTEST_SCRIPTS
  init.mac
  init_vis.mac
  vis.mac
  beam_1Mev.mac
  Test.mac
  run_10Mevents.mac
  )

foreach(_script ${THERMALSCATTERINGTEST_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


