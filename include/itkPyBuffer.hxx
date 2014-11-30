/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkPyBuffer_hxx
#define __itkPyBuffer_hxx

#include "itkPyBuffer.h"

// Support NumPy < 1.7
#ifndef NPY_ARRAY_C_CONTIGUOUS
#define NPY_ARRAY_C_CONTIGUOUS NPY_C_CONTIGUOUS
#endif

#ifndef NPY_ARRAY_F_CONTIGUOUS
#define NPY_ARRAY_F_CONTIGUOUS NPY_F_CONTIGUOUS
#endif

#ifndef NPY_ARRAY_WRITEABLE
#define NPY_ARRAY_WRITEABLE NPY_WRITEABLE
#endif

namespace itk
{

template<class TImage>
PyObject *
PyBuffer<TImage>
::GetArrayFromImage( ImageType * image, bool keepAxes )
{
  if( !image )
    {
    throw std::runtime_error("Input image is null");
    }

  image->Update();

  ComponentType *buffer =  const_cast < ComponentType *> (reinterpret_cast< const ComponentType* > ( image->GetBufferPointer() ) );
  char * data = (char *)( buffer );

  const int numberOfComponents = image->GetNumberOfComponentsPerPixel();

  const int item_type = PyTypeTraits<ComponentType>::value;

  const int numpyArrayDimension = ( numberOfComponents > 1) ? ImageDimension + 1 : ImageDimension;

  // Construct array with dimensions
  npy_intp dimensions[ numpyArrayDimension ];

  // Add a dimension if there are more than one component
  if ( numberOfComponents > 1)
    {
    dimensions[0] = numberOfComponents;
    }
  const int dimensionOffset = ( numberOfComponents > 1) ? 1 : 0;

  SizeType size = image->GetBufferedRegion().GetSize();
  for( unsigned int dim = 0; dim < ImageDimension; ++dim )
    {
    dimensions[dim + dimensionOffset] = size[dim];
    }

  if( !keepAxes )
    {
    // Reverse dimensions array
    npy_intp reverseDimensions[ numpyArrayDimension ];
    for( int dim = 0; dim < numpyArrayDimension; ++dim )
      {
      reverseDimensions[dim] = dimensions[numpyArrayDimension - dim - 1];
      }

    for( int dim = 0; dim < numpyArrayDimension; ++dim )
      {
      dimensions[dim] = reverseDimensions[dim];
      }
    }

  const int flags = (keepAxes? NPY_ARRAY_F_CONTIGUOUS : NPY_ARRAY_C_CONTIGUOUS) |
              NPY_WRITEABLE;

  PyObject * obj = PyArray_New(&PyArray_Type, numpyArrayDimension, dimensions, item_type, NULL, data, 0, flags, NULL);

  return obj;
}

template<class TImage>
const typename PyBuffer<TImage>::OutputImagePointer
PyBuffer<TImage>
::GetImageFromArray( PyObject *obj )
{
  const int elementType = PyTypeTraits<ComponentType>::value;

  PyArrayObject * array = (PyArrayObject *) PyArray_ContiguousFromObject( obj,
                                                                          elementType,
                                                                          ImageDimension,
                                                                          ImageDimension  );

  if( array == NULL )
    {
    throw std::runtime_error("Contiguous array couldn't be created from input python object");
    }

  const unsigned int imageDimension = array->nd;

  SizeType size;

  SizeValueType numberOfPixels = 1;
  for( unsigned int dim = 0; dim < imageDimension; ++dim )
    {
    size[imageDimension - dim - 1] = array->dimensions[dim];
    numberOfPixels *= array->dimensions[dim];
    }

  IndexType start;
  start.Fill( 0 );

  RegionType region;
  region.SetIndex( start );
  region.SetSize( size );

  PointType origin;
  origin.Fill( 0.0 );

  SpacingType spacing;
  spacing.Fill( 1.0 );

  typedef ImportImageFilter< ComponentType, ImageDimension > ImporterType;
  typename ImporterType::Pointer importer = ImporterType::New();
  importer->SetRegion( region );
  importer->SetOrigin( origin );
  importer->SetSpacing( spacing );
  const bool importImageFilterWillOwnTheBuffer = false;

  ComponentType * data = (ComponentType *)array->data;

  importer->SetImportPointer( data,
                              numberOfPixels,
                              importImageFilterWillOwnTheBuffer );

  importer->Update();
  OutputImagePointer output = importer->GetOutput();
  output->DisconnectPipeline();

  return output;
}

} // namespace itk

#endif
