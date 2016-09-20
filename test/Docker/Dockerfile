FROM debian:8
MAINTAINER Insight Software Consortium <community@itk.org>

RUN apt-get update && apt-get install -y \
  build-essential \
  curl \
  cmake \
  git \
  libexpat1-dev \
  libhdf5-dev \
  libjpeg-dev \
  libpng12-dev \
  libpython-dev \
  libtiff5-dev \
  ninja-build \
  python \
  python-numpy \
  swig3.0 \
  wget \
  vim \
  zlib1g-dev

RUN mkdir -p /usr/src/ITKBridgeNumPy-build
WORKDIR /usr/src

# master 2016-09-20
ENV ITK_GIT_TAG a1ad10b3b7269e494e96cfbbec64826b752de75f
RUN git clone https://itk.org/ITK.git && \
  cd ITK && \
  git checkout ${ITK_GIT_TAG} && \
  cd ../ && \
  mkdir ITK-build && \
  cd ITK-build && \
  cmake \
    -G Ninja \
    -DCMAKE_INSTALL_PREFIX:PATH=/usr \
    -DBUILD_EXAMPLES:BOOL=OFF \
    -DBUILD_TESTING:BOOL=OFF \
    -DBUILD_SHARED_LIBS:BOOL=ON \
    -DITK_WRAP_PYTHON:BOOL=ON \
    -DPYTHON_EXECUTABLE:FILEPATH=/usr/bin/python \
    -DSWIG_EXECUTABLE:FILEPATH=/usr/bin/swig3.0 \
    -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON \
    -DITK_LEGACY_REMOVE:BOOL=ON \
    -DITK_BUILD_DEFAULT_MODULES:BOOL=OFF \
    -DITK_USE_SYSTEM_LIBRARIES:BOOL=ON \
    -DModule_ITKCommon:BOOL=ON \
    -DModule_ITKTestKernel:BOOL=ON \
    ../ITK && \
  ninja && \
  find . -name '*.o' -delete

