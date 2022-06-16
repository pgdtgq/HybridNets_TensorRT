include(FindPackageHandleStandardArgs)
unset(NVBIO_FOUND)
set(NVBIO-VERSION nvbio)

find_path(Nvbio_INCLUDE_DIR NAMES nvbio PATHS ${LIB_PATH}/include/${NVBIO-VERSION} NO_DEFAULT_PATH)

# set NVBIO_FOUND
find_package_handle_standard_args(Nvbio DEFAULT_MSG Nvbio_INCLUDE_DIR)

if(NVBIO_FOUND)
    set(Nvbio_INCLUDE_DIRS ${Nvbio_INCLUDE_DIR})
endif(NVBIO_FOUND)