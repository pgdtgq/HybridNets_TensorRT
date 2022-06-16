include(FindPackageHandleStandardArgs)
unset(PCL_FOUND)
set(PCL-VERSION pcl-1.9)
find_path(PCL_INCLUDE_DIR NAMES pcl PATHS ${LIB_PATH}/include/${PCL-VERSION} NO_DEFAULT_PATH)

find_library(PCL_COMMON NAMES libpcl_common.so PATHS ${LIB_PATH}/lib/${PCL-VERSION} NO_DEFAULT_PATH)
find_library(PCL_VISUALIZATION NAMES libpcl_visualization.so PATHS ${LIB_PATH}/lib/${PCL-VERSION} NO_DEFAULT_PATH)
find_library(PCL_KDTREE NAMES libpcl_kdtree.so PATHS ${LIB_PATH}/lib/${PCL-VERSION} NO_DEFAULT_PATH)
find_library(PCL_SEARCH NAMES libpcl_search.so PATHS ${LIB_PATH}/lib/${PCL-VERSION} NO_DEFAULT_PATH)
find_library(PCL_SURFACE NAMES libpcl_surface.so PATHS ${LIB_PATH}/lib/${PCL-VERSION} NO_DEFAULT_PATH)
find_library(PCL_IO NAMES libpcl_io.so PATHS ${LIB_PATH}/lib/${PCL-VERSION} NO_DEFAULT_PATH)
find_library(PCL_RECOGNITION NAMES libpcl_recognition.so PATHS ${LIB_PATH}/lib/${PCL-VERSION} NO_DEFAULT_PATH)
find_library(PCL_STEREO NAMES libpcl_stereo.so PATHS ${LIB_PATH}/lib/${PCL-VERSION} NO_DEFAULT_PATH)
find_library(PCL_SEG NAMES libpcl_segmentation.so PATHS ${LIB_PATH}/lib/${PCL-VERSION} NO_DEFAULT_PATH)


set(PCL_LIBRARIES ${PCL_COMMON} ${PCL_VISUALIZATION} ${PCL_KDTREE} ${PCL_SEARCH} ${PCL_SURFACE} ${PCL_IO} ${PCL_RECOGNITION} ${PCL_STEREO} ${PCL_SEG})

# set PCL_FOUND
find_package_handle_standard_args(PCL DEFAULT_MSG PCL_INCLUDE_DIR PCL_LIBRARIES)


if(PCL_FOUND)
    set(PCL_LIBRARIES ${PCL_LIBRARIES})
    set(PCL_INCLUDE_DIRS ${PCL_INCLUDE_DIR})
endif(PCL_FOUND)
