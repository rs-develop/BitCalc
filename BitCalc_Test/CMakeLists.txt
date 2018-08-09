CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

PROJECT(BitCalc_Test)

#Find gtest and show status message
FIND_PACKAGE( GTest REQUIRED )
message("-- Google Test Include: ${GTEST_INCLUDE_DIRS}")
message("-- Google Test Libraries: ${GTEST_BOTH_LIBRARIES}")

ENABLE_TESTING()

INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(../BitCalc/)

SET( BitCalc_SRC
    ../BitCalc/BitCalc.cpp)

SET( BitCalc_HEADER
    ../BitCalc/BitCalc.h)

# Executable
ADD_EXECUTABLE(BitCalc_Test ${BitCalc_SRC} ${BitCalc_HEADER} BitCalc_Test.cpp)
TARGET_LINK_LIBRARIES(BitCalc_Test ${GTEST_BOTH_LIBRARIES}
                                   pthread #gtest needs pthread
                                   )

