project(data-structures)
cmake_minimum_required(VERSION 3.15)

set (CMAKE_CXX_STANDARD 17)
file(GLOB EXECUTABLES "**/*.cpp")

foreach(M ${EXECUTABLES})
    get_filename_component(dir ${M} DIRECTORY)
    get_filename_component(baseDir ${dir} NAME)

    get_filename_component(filename ${M} NAME)
    get_filename_component(execName ${M} NAME_WE)
    #string(REGEX REPLACE ".cpp" "" execName ${filename})
    add_executable(${baseDir}__${execName} ${M})
endforeach()
