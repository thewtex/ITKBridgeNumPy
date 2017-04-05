ITKBridgeNumPy
==============

.. image:: https://circleci.com/gh/InsightSoftwareConsortium/ITKBridgeNumPy.svg?style=svg
    :target: https://circleci.com/gh/InsightSoftwareConsortium/ITKBridgeNumPy

This is a port from the original WrapITK PyBuffer to an ITKv4 module.

Differences from the original PyBuffer:

- Support for VectorImage's
- Option to not swap the axes (only for GetArrayFromImage)
- Tests
- Based on the `Python Buffer Protocol <https://docs.python.org/3/c-api/buffer.html>`_ -- does not require NumPy to build.

This module is available in the ITK source tree as a Remote
module.  To enable it, set::

  ITK_WRAP_PYTHON:BOOL=ON
  Module_BridgeNumPy:BOOL=ON

in ITK's CMake build configuration. In ITK 4.12 and later, this module is
enabled by default when `ITK_WRAP_PYTHON` is enabled.

To convert an ITK image to a NumPy array::

  import itk

  PixelType = itk.ctype('float')
  Dimension = 3
  ImageType = itk.Image[PixelType, Dimension]

  image = ImageType.New()
  size = itk.Size[Dimension]()
  size.Fill(100)
  region = itk.ImageRegion[Dimension](size)
  image.SetRegions(region)
  image.Allocate()

  arr = itk.PyBuffer[ImageType].GetArrayFromImage(image)

To convert a NumPy array to an ITK image::

  import numpy as np
  import itk

  PixelType = itk.ctype('float')
  Dimension = 3
  ImageType = itk.Image[PixelType, Dimension]

  arr = np.zeros((100, 100, 100), np.float32)
  image = itk.PyBuffer[ImageType].GetImageFromArray(arr)

It is also possible to convert VNL matrices and arrays to NumPy arrays and
back::

  import numpy as np
  import itk

  ElementType = itk.ctype('float')
  vector = itk.vnl_vector[ElementType]()
  vector.set_size(8)
  arr = itk.PyVnl[ElementType].GetArrayFromVnlVector(vector)

  matrix = itk.vnl_matrix[ElementType]()
  matrix.set_size(3, 4)
  arr = itk.PyVnl[ElementType].GetArrayFromVnlMatrix(matrix)

  arr = np.zeros((100,), np.float32)
  vector = itk.PyVnl[ElementType].GetVnlVectorFromArray(arr)

  arr = np.zeros((100, 100), np.float32)
  matrix = itk.PyVnl[ElementType].GetVnlMatrixFromArray(arr)

.. warning::

  The conversions create `NumPy Views
  <https://scipy-cookbook.readthedocs.io/items/ViewsVsCopies.html>`_, i.e. it
  presents the ITK image pixel buffer in the NumPy array, and the buffer is
  shared. This means that no copies are made (which increases speed and
  reduces memory consumption). It also means that any changes in the NumPy
  array change the ITK image content. Additionally, a reference to an ITK
  image object must be available to use its NumPy array view. Using an array
  view after its source image has been deleted can results in corrupt values
  or a segfault.
