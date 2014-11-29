set(DOCUMENTATION "This modules provides methods to convert wrapped
itk::Image's to NumPy arrays and vice versa.")

itk_module(NumPyConversion
  DEPENDS
    ITKCommon
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
  )
