itk_module_test()

if(ITK_WRAP_PYTHON)
  itk_python_add_test(NAME itkDicomSliceReadPythonTest
                      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/itkPyBufferTest.py
  )
  itk_python_add_test(NAME itkPyBufferMemoryLeakTest
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/itkPyBufferMemoryLeakTest.py
  )
endif()
