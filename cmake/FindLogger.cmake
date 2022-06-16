include(FindPackageHandleStandardArgs)
unset(LOGGER_FOUND)
set(LOGGER-VERSION logger)

find_path(Logger_INCLUDE_DIR NAMES logger PATHS ${LIB_PATH}/include/${LOGGER-VERSION} NO_DEFAULT_PATH)

if(USE_LOCAL_LOGGER STREQUAL ON)
    find_library(Logger_LIBRARY NAMES logger PATHS ${LIB_PATH}/lib/${LOGGER-VERSION} NO_DEFAULT_PATH)
else()
    find_library(Logger_LIBRARY NAMES DataGather PATHS ${LIB_PATH}/lib/${LOGGER-VERSION} NO_DEFAULT_PATH)
endif()

find_package_handle_standard_args(Logger DEFAULT_MSG Logger_INCLUDE_DIR Logger_LIBRARY)

if(LOGGER_FOUND)
    set(Logger_LIBRARIES ${Logger_LIBRARY})
    set(Logger_INCLUDE_DIRS ${Logger_INCLUDE_DIR})
endif(LOGGER_FOUND)

# hide locals from GUI
mark_as_advanced(Logger_INCLUDE_DIR Logger_LIBRARY)