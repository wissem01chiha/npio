.. _install:

Installation Guide
=====================================

Binary Installation
-------------------



Build from Source
-----------------

npio can be built using cmake, meson, or bazel as build systems.  
However, we recommend using cmake, since it is the officially supported build system.

.. code-block:: bash

   git clone https://github.com/wissem01chiha/npio.git
   cd npio

CMake
~~~~~~~~~~~~~~

.. code-block:: bash

   mkdir build && cd build
   cmake ..
   make
   sudo make install

Meson
~~~~~~~~~~~~~~

.. code-block:: bash

   meson setup builddir
   meson compile -C builddir
   meson install -C builddir

Bazel
~~~~~~~~~~~~~~

.. code-block:: bash

   bazel build //:npio
   bazel run //:npio

