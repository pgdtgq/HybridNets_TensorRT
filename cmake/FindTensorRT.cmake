include(FindPackageHandleStandardArgs)
unset(TENSORRT_FOUND)
set(TensorRT-VERSION TensorRT-7.2.1.6_cuda-11.1)

find_path(TensorRT_INCLUDE_DIR NAMES NvInfer.h PATHS ${LIB_PATH}/include/${TensorRT-VERSION} NO_DEFAULT_PATH)

#customize lib libnvonnxparser_plugin  nvonnxparser.so nvonnxparser_runtime.so
find_library(NVINFER NAMES nvinfer PATHS ${LIB_PATH}/lib/${TensorRT-VERSION} NO_DEFAULT_PATH)
find_library(NVINFER_PLUGIN NAMES nvinfer_plugin PATHS ${LIB_PATH}/lib/${TensorRT-VERSION} NO_DEFAULT_PATH)
find_library(NVPARSERS NAMES nvparsers PATHS ${LIB_PATH}/lib/${TensorRT-VERSION} NO_DEFAULT_PATH)
find_library(NVONNXPARSER NAMES nvonnxparser PATHS ${LIB_PATH}/lib/${TensorRT-VERSION} NO_DEFAULT_PATH)
find_library(NVONNXPARSER_RUNTIME NAMES nvonnxparser_runtime PATHS ${LIB_PATH}/lib/${TensorRT-VERSION} NO_DEFAULT_PATH)
# set TENSORRT_FOUND
find_package_handle_standard_args(TensorRT DEFAULT_MSG TensorRT_INCLUDE_DIR NVINFER NVINFER_PLUGIN NVPARSERS NVONNXPARSER)

# set external variables for usage in CMakeLists.txt
#${SEGMENT} ${UTILS}  ${TRT_LOGING} ${TRT_ALLOCATOR} ${TRT_PLUGIN}
if(TENSORRT_FOUND)
    # set(TensorRT_LIBRARIES ${NVINFER} ${NVINFER_PLUGIN} ${NVPARSERS} ${NVONNXPARSER_STATIC} ${NVONNXPARSER_RUNTIME})
    set(TensorRT_LIBRARIES ${NVINFER} ${NVINFER_PLUGIN} ${NVPARSERS} ${NVONNXPARSER})
    set(TensorRT_INCLUDE_DIRS ${TensorRT_INCLUDE_DIR})
    set(TensorRT_LIBRARIES_DIR ${PROJECT_SOURCE_DIR}/3rdparty/tensorrt/lib)
    link_directories(${TensorRT_LIBRARIES_DIR})
endif(TENSORRT_FOUND)

mark_as_advanced(TensorRT_INCLUDE_DIR NVINFER NVINFER_PLUGIN NVPARSERS NVONNXPARSER)
