cmake_minimum_required(VERSION 2.8.3)
project(SMTPlan)

## Version number
set (SMTPlan_VERSION_MAJOR 0)
set (SMTPlan_VERSION_MINOR 1)

##-----------##
## Configure ##
##-----------##

set (PROJECT_SOURCE_DIR src)

## configure a header file for CMake settings
configure_file (
  "${PROJECT_SOURCE_DIR}/SMTPlanConfig.h.in"
  "${PROJECT_BINARY_DIR}/SMTPlanConfig.h"
)
 
## add the binary tree to the include files so that we will find SMTPlanConfig.h
include_directories("${PROJECT_BINARY_DIR}")

find_package(Boost 1.54 COMPONENTS regex REQUIRED)

##-------##
## Build ##
##-------##

## include directories
include_directories (include)
include_directories (src/VALfiles)
include_directories (src/VALfiles/src)
include_directories (src/VALfiles/include)

## required
find_package (FLEX REQUIRED)

## val sources
set(VAL_SOURCES
	src/VALfiles/src/DebugWriteController.cpp
	src/VALfiles/src/FastEnvironment.cpp
	src/VALfiles/src/FuncAnalysis.cpp
	src/VALfiles/src/SimpleEval.cpp
	src/VALfiles/src/TIM.cpp
	src/VALfiles/src/TimSupport.cpp
	src/VALfiles/src/TypedAnalyser.cpp
	src/VALfiles/src/instantiation.cpp
	src/VALfiles/src/pddl+.cpp
	src/VALfiles/src/ptree.cpp
	src/VALfiles/src/typecheck.cpp)

## SMTPLAN sources
set(SMTPLAN_SOURCES
	src/SMTPlan.cpp
	src/Encoder.cpp)

## Declare cpp executables
add_executable(SMTPlan ${SMTPLAN_SOURCES} ${VAL_SOURCES})
target_link_libraries(SMTPlan ${Boost_LIBRARIES} z3)

# add the install targets
install (TARGETS SMTPlan DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/SMTPlanConfig.h" DESTINATION include)
