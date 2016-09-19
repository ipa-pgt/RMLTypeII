cmake_minimum_required(VERSION 2.8.3)
project(RMLTypeII)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -fno-unsafe-math-optimizations")

find_package(PythonLibs 2.7.9 REQUIRED)

include_directories(
  include
  pybind11/include
  ${PYTHON_INCLUDE_DIRS}
  )

add_library(TypeIIRML SHARED
  src/TypeIIRML/ReflexxesAPI.cpp
  src/TypeIIRML/TypeIIRMLCalculatePositionalExtrems.cpp
  src/TypeIIRML/TypeIIRMLDecisionTree1A.cpp
  src/TypeIIRML/TypeIIRMLDecisionTree1B.cpp
  src/TypeIIRML/TypeIIRMLDecisionTree1C.cpp
  src/TypeIIRML/TypeIIRMLDecisionTree2.cpp
  src/TypeIIRML/TypeIIRMLDecisions.cpp
  src/TypeIIRML/TypeIIRMLFallBackStrategy.cpp
  src/TypeIIRML/TypeIIRMLIsPhaseSynchronizationPossible.cpp
  src/TypeIIRML/TypeIIRMLPolynomial.cpp
  src/TypeIIRML/TypeIIRMLPosition.cpp
  src/TypeIIRML/TypeIIRMLQuicksort.cpp
  src/TypeIIRML/TypeIIRMLSetupModifiedSelectionVector.cpp
  src/TypeIIRML/TypeIIRMLStep1.cpp
  src/TypeIIRML/TypeIIRMLStep1IntermediateProfiles.cpp
  src/TypeIIRML/TypeIIRMLStep1Profiles.cpp
  src/TypeIIRML/TypeIIRMLStep2.cpp
  src/TypeIIRML/TypeIIRMLStep2IntermediateProfiles.cpp
  src/TypeIIRML/TypeIIRMLStep2PhaseSynchronization.cpp
  src/TypeIIRML/TypeIIRMLStep2Profiles.cpp
  src/TypeIIRML/TypeIIRMLStep2WithoutSynchronization.cpp
  src/TypeIIRML/TypeIIRMLStep3.cpp
  src/TypeIIRML/TypeIIRMLVelocity.cpp
  src/TypeIIRML/TypeIIRMLVelocityCalculatePositionalExtrems.cpp
  src/TypeIIRML/TypeIIRMLVelocityFallBackStrategy.cpp
  src/TypeIIRML/TypeIIRMLVelocityIsPhaseSynchronizationPossible.cpp
  src/TypeIIRML/TypeIIRMLVelocityMethods.cpp
  src/TypeIIRML/TypeIIRMLVelocitySetupPhaseSyncSelectionVector.cpp
  )

add_executable(01_RMLPositionSampleApplication
  src/RMLPositionSampleApplications/01_RMLPositionSampleApplication.cpp)
target_link_libraries(01_RMLPositionSampleApplication TypeIIRML)
add_executable(02_RMLPositionSampleApplication
  src/RMLPositionSampleApplications/02_RMLPositionSampleApplication.cpp)
target_link_libraries(02_RMLPositionSampleApplication TypeIIRML)
add_executable(03_RMLPositionSampleApplication
  src/RMLPositionSampleApplications/03_RMLPositionSampleApplication.cpp)
target_link_libraries(03_RMLPositionSampleApplication TypeIIRML)
add_executable(07_RMLPositionSampleApplication
  src/RMLPositionSampleApplications/07_RMLPositionSampleApplication.cpp)
target_link_libraries(07_RMLPositionSampleApplication TypeIIRML)


add_library(reflexxes_motion_library SHARED
  src/TypeIIRMLPython.cpp)
target_link_libraries(reflexxes_motion_library
  TypeIIRML
  ${PYTHON_LIBRARIES}
  )
set_target_properties(reflexxes_motion_library PROPERTIES PREFIX "")
set_target_properties(reflexxes_motion_library PROPERTIES SUFFIX ".so")
