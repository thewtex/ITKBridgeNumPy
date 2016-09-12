ITKBridgeNumPy
==============

.. image:: https://circleci.com/gh/InsightSoftwareConsortium/ITKBridgeNumPy.svg?style=svg
    :target: https://circleci.com/gh/InsightSoftwareConsortium/ITKBridgeNumPy

This is a port from the original WrapITK PyBuffer to an ITKv4 module.

Differences from the original PyBuffer:

- Support for VectorImages (only for GetArrayFromImage)
- Option to not swap the axes (only for GetArrayFromImage)
- Some rudimental tests
- No support for numarray

TODO:

- Add features also to GetImageFromArray
- Improve tests
