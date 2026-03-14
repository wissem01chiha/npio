Installation
----------------

Build from Source
~~~~~~~~~~~~~~~~~~~~~

CMake
^^^^^^^^^^^

| `CMake <https://cmake.org>`__ 3.24 or higher is required.The default
  installation directory is ``/usr/local``.
| To specify a different directory, add
  ``-DCMAKE_INSTALL_PREFIX=/path/to/install/dir`` to the CMake
  invocation in step 4.

1. Clone the repository:

.. code:: shell

    git clone https://github.com/wissem01chiha/npio

2. Configure the build:

.. code:: shell

   cmake -B build -DCMAKE_INSTALL_PREFIX=~/build/install

3. Build and install:

.. code:: shell

   ninja install

Meson
~~~~~~~~~~~

Meson >= 1.10.0 is required. For more information, refer to
`Quick-guide <https://mesonbuild.com/Quick-guide.html>`__

.. code:: shell

   meson setup builddir 
   cd builddir 
   meson compile 

Then install the library using:

.. code:: shell

   meson install

Bazel
~~~~~~~~~~~

   [!NOTE] Bazel is not yet supported. Please use `cmake <#11-cmake>`__
   or `meson <#12-menson>`__ instead.

Testing
-----------

.. _cmake-1:

CMake
~~~~~~~~~

.. _meson-1:

Meson
~~~~~~~~~

To run project tests:

.. code:: shell

   meson test 

.. _bazel-1:

Bazel
~~~~~~~~~

   [!NOTE] Bazel tests are not yet supported. Use `cmake <#11-cmake>`__
   or `meson <#12-menson>`__ to run tests
