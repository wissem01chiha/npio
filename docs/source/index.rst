
Welcome to the npio documentation
==================================

.. raw:: html

.. image:: https://github.com/wissem01chiha/npio/actions/workflows/ubuntu.yml/badge.svg
   :target: https://github.com/wissem01chiha/npio/actions/workflows/ubuntu.yml
   :alt: Ubuntu

.. image:: https://img.shields.io/appveyor/build/wissem01chiha/npio
   :alt: AppVeyor Build

.. image:: https://github.com/wissem01chiha/npio/actions/workflows/codeql.yml/badge.svg
   :alt: Code QL

.. image:: https://img.shields.io/github/license/wissem01chiha/npio
   :alt: GitHub License

.. image:: https://www.codefactor.io/repository/github/wissem01chiha/npio/badge
   :target: https://www.codefactor.io/repository/github/wissem01chiha/npio
   :alt: CodeFactor


-------------

.. toctree::
   :maxdepth: 1

   install
   api
   change


npio is a C++11 copy of `cnpy <https://github.com/rogersce/cnpy>`__
writtin by Carl Rogers librray for reading/writing `numpy <>`__ npy and
npz files which is not actively maintained.

NumPy offers the ``save`` method for easy saving of arrays into .npy and
``savez`` for zipping multiple .npy arrays together into a .npz file.

``cnpy`` lets you read and write to these formats in C++.

The motivation comes from scientific programming where large amounts of
data are generated in C++ and analyzed in Python.

Writing to .npy has the advantage of using low-level C++ I/O (fread and
fwrite) for speed and binary format for size. The .npy file header takes
care of specifying the size, shape, and data type of the array, so
specifying the format of the data is unnecessary.

Loading data written in numpy formats into C++ is equally simple, but
requires you to type-cast the loaded data to the type of your choice.

1.0 Installation
================

Default installation directory is /usr/local. To specify a different
directory, add ``-DCMAKE_INSTALL_PREFIX=/path/to/install/dir`` to the
cmake invocation in step 4.

1. get `cmake <www.cmake.org>`__
2. create a build directory, say $HOME/build
3. cd $HOME/build
4. cmake /path/to/cnpy
5. make
6. make install

2.0 Using
=========

To use, ``#include"cnpy.h"`` in your source code. Compile the source
code mycode.cpp as

.. code:: bash

   g++ -o mycode mycode.cpp -L/path/to/install/dir -lcnpy -lz --std=c++11

3.0 Description
===============

There are two functions for writing data: ``npy_save`` and ``npz_save``.

There are 3 functions for reading: - ``npy_load`` will load a .npy file.
- ``npz_load(fname)`` will load a .npz and return a dictionary of
NpyArray structues. - ``npz_load(fname,varname)`` will load and return
the NpyArray for data varname from the specified .npz file.

The data structure for loaded data is below. Data is accessed via the
``data<T>()``-method, which returns a pointer of the specified type
(which must match the underlying datatype of the data). The array shape
and word size are read from the npy header.

.. code:: cpp

   struct NpyArray {
       std::vector<size_t> shape;
       size_t word_size;
       template<typename T> T* data();
   };

See `example </example/>`__ folder for examples of how to use the
library.

4.0 License
-----------

.. |Ubuntu| image:: https://github.com/wissem01chiha/npio/actions/workflows/ubuntu.yml/badge.svg
   :target: https://github.com/wissem01chiha/npio/actions/workflows/ubuntu.yml
.. |AppVeyor Build| image:: https://img.shields.io/appveyor/build/wissem01chiha/npio
.. |GitHub License| image:: https://img.shields.io/github/license/wissem01chiha/npio
.. |CodeFactor| image:: https://www.codefactor.io/repository/github/wissem01chiha/npio/badge
   :target: https://www.codefactor.io/repository/github/wissem01chiha/npio
