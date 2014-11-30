itk_module_test()

set(BridgeNumPyTests
  itkPyBufferTest.cxx
  )

set(BridgeNumPy-Test_LIBRARIES "${BridgeNumPy-Test_LIBRARIES};${PYTHON_LIBRARY}")

CreateTestDriver(BridgeNumPy "${BridgeNumPy-Test_LIBRARIES}"
  "${BridgeNumPyTests}")

itk_add_test(NAME itkPyBufferTest
  COMMAND BridgeNumPyTestDriver itkPyBufferTest)
