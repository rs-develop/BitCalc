
CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

PROJECT(BitCalc)

# ENABLE C++ 11
SET (CMAKE_CXX_STANDARD 11)

# SET BUILD TYPE IF NO BUILD TYPE WAS SPECIFIED 
IF (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
ENDIF ()

# PRINT BUILD TYPE
IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Build-Type set to Debug")
ELSEIF (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Release")
    SET(CMAKE_BUILD_TYPE Release)
    message("Build in Release-Mode (standard mode)")
ENDIF ()

# IF BUILD IS DEBUG - BUILD TEST
IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    ADD_SUBDIRECTORY(BitCalc_Test)
ENDIF ()

ADD_SUBDIRECTORY(BitCalc_Console)
