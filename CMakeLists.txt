CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

project(surface_interpolation)

include_directories("/home/alex/libInterpolate/src")

find_package(libInterpolate REQUIRED)

add_executable(surface_interpolation
${CMAKE_SOURCE_DIR}/surface_generator.h
${CMAKE_SOURCE_DIR}/octave_codegen.h

${CMAKE_SOURCE_DIR}/surface_generator.cpp
${CMAKE_SOURCE_DIR}/octave_codegen.cpp

${CMAKE_SOURCE_DIR}/surface_interpolation.cpp

)

target_link_libraries( surface_interpolation libInterpolate::Interpolate )

