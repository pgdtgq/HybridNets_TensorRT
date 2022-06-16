include(FindPackageHandleStandardArgs)
unset(VTK_FOUND)
set(VTK-VERSION vtk-6.3)

find_path(VTK_INCLUDE_DIR NAMES vtksys PATHS ${LIB_PATH}/include/${VTK-VERSION} NO_DEFAULT_PATH)

file(GLOB_RECURSE VTK_LIBRARIES "${LIB_PATH}/lib/${VTK-VERSION}/*.*")

# set VTK_FOUND
find_package_handle_standard_args(VTK DEFAULT_MSG VTK_INCLUDE_DIR)

if(VTK_FOUND)
    set(VTK_LIBRARIES ${VTK_LIBRARIES})
    set(VTK_INCLUDE_DIRS ${VTK_INCLUDE_DIR})
endif(VTK_FOUND)