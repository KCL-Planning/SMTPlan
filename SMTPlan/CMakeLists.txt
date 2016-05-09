cmake_minimum_required(VERSION 2.8.3)
project(SMTPlan)

## Version number
set (SMTPlan_VERSION_MAJOR 0)
set (SMTPlan_VERSION_MINOR 9)

##-----------##
## Configure ##
##-----------##

SET(CMAKE_CXX_FLAGS "-std=c++0x")

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
find_package(SymEngine 0.1.0 CONFIG)
find_package(GMP REQUIRED)
find_package(MPFR REQUIRED)
find_package(Boost REQUIRED thread)

## include directories
include_directories (include)
include_directories (src/VALfiles)
include_directories (src/VALfiles/src)
include_directories (src/VALfiles/include)
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${SYMENGINE_INCLUDE_DIRS})
include_directories(${GMP_INCLUDE_DIR})
include_directories(${MPFR_INCLUDE_DIR})

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
	src/Algebraist.cpp
	src/Encoder.cpp)

## Declare cpp executables
add_executable(SMTPlan ${SMTPLAN_SOURCES} ${VAL_SOURCES})
target_link_libraries(SMTPlan ${Boost_LIBRARIES} z3 ${Boost_LIBRARIES} ${GMP_LIBRARIES} ${MPFR_LIBRARIES})

#add_executable(test_python src/test_python.cpp)
#target_link_libraries(test_python ${Boost_LIBRARIES} ${GMP_LIBRARIES} ${MPFR_LIBRARIES})

# add the install targets
install (TARGETS SMTPlan DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/SMTPlanConfig.h" DESTINATION include)
