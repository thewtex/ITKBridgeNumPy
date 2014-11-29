list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_LIST_DIR}/CMake")

find_package(PythonLibs REQUIRED)
find_package(NumPy REQUIRED)

if(NOT NUMPY_FOUND)
  message(FATAL_ERROR "NumPy not found.

  Please set NUMPY_INCLUDE_DIR to the location of numpy/arrayobject.h.")
endif()
