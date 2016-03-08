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

##-------##
## Build ##
##-------##

## include directories
include_directories (include)
include_directories (src/VALfiles)

## required
find_package (FLEX REQUIRED)

## val sources
set(VAL_SOURCES
	src/VALfiles/DebugWriteController.cpp
	src/VALfiles/FastEnvironment.cpp
	src/VALfiles/FuncAnalysis.cpp
	src/VALfiles/SASActions.cpp
	src/VALfiles/SimpleEval.cpp
	src/VALfiles/TIM.cpp
	src/VALfiles/TimSupport.cpp
	src/VALfiles/ToFunction.cpp
	src/VALfiles/TypedAnalyser.cpp
	src/VALfiles/ValidatorAPI.cpp
	src/VALfiles/instantiation.cpp
	src/VALfiles/pddl+.cpp
	src/VALfiles/ptree.cpp
	src/VALfiles/typecheck.cpp
	src/VALfiles/Validator.cpp
	src/VALfiles/Action.cpp
	src/VALfiles/Proposition.cpp
	src/VALfiles/FuncExp.cpp
	src/VALfiles/RepairAdvice.cpp
	src/VALfiles/State.cpp
	src/VALfiles/Plan.cpp
	src/VALfiles/Ownership.cpp
	src/VALfiles/Environment.cpp
	src/VALfiles/Events.cpp
	src/VALfiles/Polynomial.cpp
	src/VALfiles/TrajectoryConstraints.cpp
	src/VALfiles/RobustAnalyse.cpp
	src/VALfiles/PrettyPrinter.cpp
	src/VALfiles/random.cpp
	src/VALfiles/LaTeXSupport.cpp
	src/VALfiles/Utils.cpp)

## SMTPLAN sources
set(SMTPLAN_SOURCES
	src/SMTPlan.cpp
	src/Parser.cpp
	src/Encoder.cpp
	src/Grounder.cpp)

## Declare cpp executables
add_executable(SMTPlan ${SMTPLAN_SOURCES} ${VAL_SOURCES})

# add the install targets
install (TARGETS SMTPlan DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/SMTPlanConfig.h" DESTINATION include)
