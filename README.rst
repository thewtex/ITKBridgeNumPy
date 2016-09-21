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

in ITK's CMake build configuration.
