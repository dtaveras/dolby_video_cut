######################################################################
# Automatically generated by qmake (2.01a) Tue Apr 22 07:20:13 2014
######################################################################

TEMPLATE = app
TARGET = 

CONFIG += console link_pkgconfig
PKGCONFIG += opencv
QT += opengl

# Input
HEADERS += glWindow.h \
           Worker.h \
           QCustomGraph/qcustomplot.h \
           QCustomGraph/qcustomplotwidget.h

SOURCES += glWindow.cpp \
           main.cpp \
           Worker.cpp \
           QCustomGraph/qcustomplot.cpp \
           QCustomGraph/qcustomplotwidget.cpp

######################################################################
# Variables necessary for Cuda Compilation and Linking
######################################################################
OTHER_FILES += kernel.cu
CUDA_SOURCES += kernel.cu
CUDA_SDK = "/Developer/NVIDIA/CUDA-5.5"   # Path to cuda SDK install
CUDA_DIR = "/Developer/NVIDIA/CUDA-5.5"            # Path to cuda toolkit install

# DO NOT EDIT BEYOND THIS UNLESS YOU KNOW WHAT YOU ARE DOING....
SYSTEM_NAME = unix         # Depending on your system either 'Win32', 'x64', or 'Win64'
SYSTEM_TYPE = 64            # '32' or '64', depending on your system
CUDA_ARCH = sm_20   # sm_21 Type of CUDA architecture, for example 'compute_10', 'compute_11', 'sm_10'
NVCC_OPTIONS = --use_fast_math

INCLUDEPATH += $$CUDA_DIR/include

# library directories
QMAKE_LIBDIR += $$CUDA_DIR/lib/

CUDA_OBJECTS_DIR = ./


# Add the necessary libraries
CUDA_LIBS = /Developer/NVIDIA/CUDA-5.5/lib/libcudart.dylib

# The following makes sure all path names (which often include spaces) are put between quotation marks
CUDA_INC = $$join(INCLUDEPATH,'" -I"','-I"','"')
#LIBS += $$join(CUDA_LIBS,'.so ', '', '.so')
LIBS += $$CUDA_LIBS

# Configuration of the Cuda compiler
CONFIG(debug, debug|release) {
    # Debug mode
    cuda_d.input = CUDA_SOURCES
    cuda_d.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
    cuda_d.commands = $$CUDA_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda_d.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda_d
}
else {
    # Release mode
    cuda.input = CUDA_SOURCES
    cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
    cuda.commands = $$CUDA_DIR/bin/nvcc $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda
}
