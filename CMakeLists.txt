CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

project(surface_interpolation)

if (UNIX)
    include_directories("/home/alex/libInterpolate/src")
    include_directories("/usr/share/eigen3/")
    find_package(libInterpolate REQUIRED)
else ()
    include_directories("C:\\Boost\\include\\boost-1_76"
    "C:\\Users\\stell\\source\\repos\\eigen-3.4-rc1"
    "C:\\Users\\stell\\source\repos\\libInterpolate\\src")
endif (UNIX)

add_executable(surface_interpolation
${CMAKE_SOURCE_DIR}/surface_generator.h
${CMAKE_SOURCE_DIR}/octave_codegen.h

${CMAKE_SOURCE_DIR}/surface_generator.cpp
${CMAKE_SOURCE_DIR}/octave_codegen.cpp

${CMAKE_SOURCE_DIR}/surface_interpolation.cpp

)

if (UNIX)
    target_link_libraries( surface_interpolation libInterpolate::Interpolate )
endif (UNIX)


