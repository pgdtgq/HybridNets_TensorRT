include(FindPackageHandleStandardArgs)
unset(EIGEN_FOUND)
set(EIGEN_VERSION eigen-3.4)
find_path(Eigen_INCLUDE_DIR NAMES Eigen PATHS ${LIB_PATH}/include/${EIGEN_VERSION} NO_DEFAULT_PATH)

# set PCL_FOUND
find_package_handle_standard_args(Eigen DEFAULT_MSG Eigen_INCLUDE_DIR)

if(EIGEN_FOUND)
    set(Eigen_INCLUDE_DIRS ${Eigen_INCLUDE_DIR})
endif(EIGEN_FOUND)