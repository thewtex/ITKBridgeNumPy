set(DOCUMENTATION "This modules provides methods to convert wrapped
itk::Image's to NumPy arrays and vice versa.")

itk_module(BridgeNumPy
  DEPENDS
    ITKCommon
  TEST_DEPENDS
    ITKTestKernel
  EXCLUDE_FROM_DEFAULT
  DESCRIPTION
    "${DOCUMENTATION}"
  )
