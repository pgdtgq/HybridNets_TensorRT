include(FindPackageHandleStandardArgs)
unset(SOPHUS_FOUND)
set(SOPHUS-VERSION Sophus)
find_path(Sophus_INCLUDE_DIR NAMES sophus PATHS ${LIB_PATH}/include/${SOPHUS-VERSION} NO_DEFAULT_PATH)

# set SOPHUS_FOUND
find_package_handle_standard_args(Sophus DEFAULT_MSG Sophus_INCLUDE_DIR)

if(SOPHUS_FOUND)
    set(Sophus_INCLUDE_DIRS ${Sophus_INCLUDE_DIR})
endif(SOPHUS_FOUND)