cmake_minimum_required(VERSION 2.8.3)
project(SMTPlan)

## Version number
set (SMTPlan_VERSION_MAJOR 0)
set (SMTPlan_VERSION_MINOR 9)

##-----------##
## Configure ##
##-----------##

set(CMAKE_CXX_FLAGS "-std=c++0x")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules" "${CMAKE_SOURCE_DIR}/cmake_modules/yacma")
set (PROJECT_SOURCE_DIR src)

## configure a header file for CMake settings
configure_file (
  "${PROJECT_SOURCE_DIR}/SMTPlanConfig.h.in"
  "${PROJECT_BINARY_DIR}/SMTPlanConfig.h"
)
 
## add the binary tree to the include files so that we will find SMTPlanConfig.h
include_directories("${PROJECT_BINARY_DIR}")

##-------##
## Build ##
##-------##

## required
find_package(FLEX REQUIRED)
find_package(PythonLibs REQUIRED)
FIND_PACKAGE(GMP REQUIRED)
MESSAGE(STATUS "GMP library found.")
MESSAGE(STATUS "GMP include dir is: ${GMP_INCLUDE_DIR}")
MESSAGE(STATUS "GMP library is: ${GMP_LIBRARIES}")
FIND_PACKAGE(MPFR REQUIRED)
MESSAGE(STATUS "MPFR library found.")
MESSAGE(STATUS "MPFR include dir is: ${MPFR_INCLUDE_DIR}")
MESSAGE(STATUS "MPFR library is: ${MPFR_LIBRARIES}")
find_package(Boost REQUIRED thread)

## include directories
include_directories (include)
include_directories (src/VALfiles)
include_directories (src/VALfiles/parsing)
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${SYMENGINE_INCLUDE_DIRS})
include_directories(${GMP_INCLUDE_DIR})
include_directories(${MPFR_INCLUDE_DIR})

## val sources
set(VAL_SOURCES
	src/VALfiles/parsing/DebugWriteController.cpp
	src/VALfiles/FastEnvironment.cpp
	src/VALfiles/FuncAnalysis.cpp
	src/VALfiles/SimpleEval.cpp
	src/VALfiles/TIM.cpp
	src/VALfiles/TimSupport.cpp
	src/VALfiles/TypedAnalyser.cpp
	src/VALfiles/instantiation.cpp
	src/VALfiles/parsing/pddl+.cpp
	src/VALfiles/parsing/ptree.cpp
	src/VALfiles/typecheck.cpp)

## SMTPLAN sources
set(SMTPLAN_SOURCES
	src/SMTPlan.cpp
	src/Algebraist.cpp
	src/EncoderHappening.cpp
	src/EncoderFluent.cpp)

## Declare cpp executables
add_executable(SMTPlan ${SMTPLAN_SOURCES} ${VAL_SOURCES})
target_link_libraries(SMTPlan ${Boost_LIBRARIES} z3 ${Boost_LIBRARIES} ${GMP_LIBRARIES} ${MPFR_LIBRARIES})

#add_executable(test_python src/test_python.cpp)
#target_link_libraries(test_python ${Boost_LIBRARIES} ${GMP_LIBRARIES} ${MPFR_LIBRARIES})

# add the install targets
install (TARGETS SMTPlan DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/SMTPlanConfig.h" DESTINATION include)
