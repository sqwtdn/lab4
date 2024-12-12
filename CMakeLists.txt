cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Lab_4)

find_package(Geant4 REQUIRED ui_all vis_all)
find_package(ROOT REQUIRED)

include(${Geant4_USE_FILE})
include(${ROOT_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB MACRO_FILES "*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(lab4 lab4.cc ${sources} ${headers})
target_link_libraries(lab4 ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

add_custom_target(Lab_4 DEPENDS lab4)