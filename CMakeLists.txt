project(BridgeNumPy)

set(BridgeNumPy_SYSTEM_INCLUDE_DIRS "${NUMPY_INCLUDE_DIR};${PYTHON_INCLUDE_DIR}")

itk_module_impl()
