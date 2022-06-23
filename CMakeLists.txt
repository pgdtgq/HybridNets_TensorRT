cmake_minimum_required(VERSION 3.18)
project(HybridNets_TensorRT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_MATH_DISABLE_FLOAT128")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -Wno-error=deprecated-declarations -Wno-deprecated-declarations -Wno-format-security")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
############################ set debug/release version #######################
if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    message(${CMAKE_BUILD_TYPE})
    SET(LIBRATY_NAME "hybridnets")
elseif (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    message(${CMAKE_BUILD_TYPE})
    SET(LIBRATY_NAME "hybridnetsd")
endif ()

############################ set output path #################################
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

############################ set lib path #################################
set(LIB_PATH /opt/PandaBusLibs_18.04)
message("PandaBusLibs path: ${LIB_PATH}")

############################ set cuda-toolkit path #################################
set(CUDA-VERSION cuda-11.1)
set(CUDA_TOOLKIT_ROOT_DIR /usr/local/${CUDA-VERSION})

############################# find library #################################
find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED)
#find_package(PCL REQUIRED)
find_package(TensorRT REQUIRED)
find_package(Logger REQUIRED)
#find_package(Flann REQUIRED)
#find_package(Openmpi REQUIRED)
find_package(Boost REQUIRED)
#find_package(Sophus REQUIRED)
#find_package(Nvbio REQUIRED)
#find_package(Eigen REQUIRED)
#find_package(Flann REQUIRED)
#find_package(VTK REQUIRED)
find_package(ZLIB REQUIRED)

############################# include directories #################################
include_directories(${CUDA_INCLUDE_DIRS} BEFORE)
include_directories(${OpenCV_INCLUDE_DIRS} BEFORE)
#include_directories(${PCL_INCLUDE_DIRS} BEFORE)
include_directories(${TensorRT_INCLUDE_DIRS} BEFORE)
include_directories(${Logger_INCLUDE_DIRS} BEFORE)
#include_directories(${Flann_INCLUDE_DIRS} BEFORE)
include_directories(${Boost_INCLUDE_DIRS} BEFORE)
#include_directories(${Eigen_INCLUDE_DIRS} BEFORE)
#include_directories(${VTK_INCLUDE_DIRS} BEFORE)
#include_directories(${Sophus_INCLUDE_DIRS} BEFORE)
#include_directories(${Nvbio_INCLUDE_DIRS} BEFORE)
include_directories(${ZLIB_INCLUDE_DIRS})

include_directories(.
        trt
        trt/plugin
        trt/plugin/CuteSamplePlugin
        trt/plugin/CuteSampleDynamicExtPlugin
        HybridNets/
        base/
        )

############################ Specify src code directory #################################
file(GLOB_RECURSE TRT
        trt/*.cpp
        trt/plugin/*.cpp
        trt/plugin/CuteSampleDynamicExtPlugin/*.cpp
        trt/plugin/CuteSamplePlugin/*.cpp
        )

file(GLOB_RECURSE HYBRIDNETS
        HybridNets/*.cpp)
file(GLOB src_file ${TRT} ${HYBRIDNETS})

######################### generate .so library ########################################
set(DEPEND_LIBRARIES ${TensorRT_LIBRARIES} ${OpenCV_LIBRARIES}
        ${CUDA_LIBRARIES} ${Boost_LIBRARIES}
        ${Logger_LIBRARIES}  ${ZLIB_LIBRARIES})
link_libraries(${DEPEND_LIBRARIES})
cuda_add_library(${LIBRATY_NAME} SHARED ${src_file})
########################### generate executable file #####################################
file(GLOB_RECURSE SRC_PRJ_MAIN main/*.cpp test/*.hpp)
add_executable(HybridNets_TensorRT ${SRC_PRJ_MAIN})
target_link_libraries(HybridNets_TensorRT ${LIBRATY_NAME} )

message(STATUS "CMake configure finished.")

