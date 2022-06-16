include(FindPackageHandleStandardArgs)
unset(OPENMPI_FOUND)
set(OPENMPI openmpi)

find_library(MPI NAMES libmpi.so PATHS ${LIB_PATH}/lib/${OPENMPI} NO_DEFAULT_PATH)
find_library(MPI_CXX NAMES libmpi_cxx.so PATHS ${LIB_PATH}/lib/${OPENMPI} NO_DEFAULT_PATH)
find_library(OPEN_RTE NAMES libopen-rte.so PATHS ${LIB_PATH}/lib/${OPENMPI} NO_DEFAULT_PATH)
find_library(OPEN_PAL NAMES libopen-pal.so PATHS ${LIB_PATH}/lib/${OPENMPI} NO_DEFAULT_PATH)

# set MPI_FOUND
find_package_handle_standard_args(Openmpi DEFAULT_MSG MPI MPI_CXX OPEN_RTE OPEN_PAL)

if(OPENMPI_FOUND)
    set(Openmpi_LIBRARIES ${MPI} ${MPI_CXX} ${OPEN_RTE} ${OPEN_PAL})
endif(OPENMPI_FOUND)