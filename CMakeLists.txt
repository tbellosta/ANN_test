cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME ANN_test)
project(${PROJECT_NAME})

# -------------------------------------------------------------------------------------- Compiler options
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -mtune=native -funroll-loops")

# -------------------------------------------------------------------------------------- Setup paths
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BIN_DIR ${ROOT_DIR}/bin)
set(INC_DIR ${ROOT_DIR}/include)
set(SRC_DIR ${ROOT_DIR}/src)
set(LIB_DIR ${ROOT_DIR}/../ANN_threadsafe)
set(EXEC_DIR ${ROOT_DIR}/tools)

# -------------------------------------------------------------------------------------- Source files
file(GLOB SOURCE src/*.cpp
        include/*.h
        include/*.hpp)

include_directories(
        include
        src
        ${LIB_DIR}/include)

link_directories(${LIB_DIR}/lib)

# -------------------------------------------------------------------------------------- Linking and libraries
set(LIBS libANN.a)
find_package(OpenMP REQUIRED)

# -------------------------------------------------------------------------------------- Find LAPACK


# --------------------------------------------------------------------------------------- UMFPACK

# -------------------------------------------------------------------------------------- MorphoGen
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})

add_library(${PROJECT_NAME} ${SOURCE})

file(GLOB TOOLS ${EXEC_DIR}/*.cpp)
#link_directories(${BIN_DIR})

foreach( sourcefile ${TOOLS} )
    string( REPLACE ".cpp" "" file ${sourcefile} )
    get_filename_component(file ${file} NAME)
    if (${file} MATCHES ${PROJECT_NAME})
        set(file ${PROJECT_NAME}-bin)
    endif()
    add_executable( ${file} ${sourcefile} )
    target_link_libraries( ${file} ${PROJECT_NAME} ${LIBS} OpenMP::OpenMP_CXX)
endforeach( sourcefile ${TOOLS} )

set_target_properties(${PROJECT_NAME}-bin
        PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
