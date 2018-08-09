CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

PROJECT(BitCalc_Console)

INCLUDE_DIRECTORIES(../BitCalc/)

SET( BitCalc_SRC
    ../BitCalc/BitCalc.cpp
)

SET( BitCalc_HEADER
    ../BitCalc/BitCalc.h
)

#Executable
ADD_EXECUTABLE(BitCalc ${BitCalc_SRC} ${BitCalc_HEADER} ../BitCalc_Console/BitCalc_Console.cpp)
TARGET_LINK_LIBRARIES(BitCalc ${GTEST_BOTH_LIBRARIES})

#Install
IF (CMAKE_CONFIGURATION_TYPES STREQUAL "Release")
    message("-- BitCalc will installed in Release-Mode to ${CMAKE_INSTALL_PREFIX}/bin")
    INSTALL(TARGETS BitCalc DESTINATION bin CONFIGURATIONS Release)
ENDIF()
