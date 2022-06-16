include(FindPackageHandleStandardArgs)
unset(FLANN_FOUND)
set(FLANN-VERSION flann-1.9.1)

find_path(Flann_ROOT_DIR NAMES flann PATHS ${LIB_PATH}/include/${FLANN-VERSION} NO_DEFAULT_PATH)
find_path(Flann_INCLUDE_DIR NAMES flann.h PATHS ${LIB_PATH}/include/${FLANN-VERSION}/flann NO_DEFAULT_PATH)
find_library(FLANN_CUDA NAMES flann_cuda_s PATHS ${LIB_PATH}/lib/${FLANN-VERSION} NO_DEFAULT_PATH)

# set FLANN_FOUND
find_package_handle_standard_args(Flann DEFAULT_MSG  Flann_INCLUDE_DIR Flann_ROOT_DIR FLANN_CUDA)

if(FLANN_FOUND)
    set(Flann_INCLUDE_DIRS ${Flann_INCLUDE_DIR} ${Flann_ROOT_DIR})
    set(Flann_LIBRARIES ${FLANN_CUDA})
endif(FLANN_FOUND)