itk_module_test()

if(ITK_WRAP_PYTHON AND NOT "${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR}" VERSION_LESS 4.11)
  itk_python_add_test(NAME itkPyBufferTest
                      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/itkPyBufferTest.py
  )
  itk_python_add_test(NAME itkPyVnlTest
                      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/itkPyVnlTest.py
  )
  itk_python_add_test(NAME itkPyBufferMemoryLeakTest
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/itkPyBufferMemoryLeakTest.py
  )
endif()
