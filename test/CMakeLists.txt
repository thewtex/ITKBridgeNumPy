itk_module_test()

set(NumPyConversionTests
  itkPyBufferTest.cxx
  )

set(NumPyConversion-Test_LIBRARIES "${NumPyConversion-Test_LIBRARIES};${PYTHON_LIBRARY}")

CreateTestDriver(NumPyConversion "${NumPyConversion-Test_LIBRARIES}"
  "${NumPyConversionTests}")

itk_add_test(NAME itkPyBufferTest
  COMMAND NumPyConversionTestDriver itkPyBufferTest)
