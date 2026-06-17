
**Npio** is a C99 version of [cnpy](https://github.com/rogersce/cnpy), written by [Carl Rogers](https://github.com/rogersce). It is a library for reading and writing [NumPy](https://numpy.org/doc/stable/reference/generated/numpy.lib.format.html) **.npy** and **.npz** files, which is no longer actively maintained.

[NumPy](https://numpy.org/doc/) provides the [save](https://numpy.org/doc/stable/reference/generated/numpy.save.html#numpy.save) method for saving arrays into **.npy** files and [savez](https://numpy.org/doc/stable/reference/generated/numpy.savez.html#numpy.savez) for zipping multiple .npy arrays together into a **.npz** file. Npio allows you to read and write these formats in C or C++

Please feel free to open an [issue](https://github.com/wissem01chiha/npio/issues). I will try to address any concerns as best I can.

## Installation

### Build from Source

#### CMake

[CMake](https://cmake.org) 3.24 or higher is required.The default
  installation directory is ``/usr/local``.

To specify a different directory, add
  ``-DCMAKE_INSTALL_PREFIX=/path/to/install/dir`` to the CMake
  invocation in step 4.

1. Clone the repository:

```shell
    git clone https://github.com/wissem01chiha/npio
```

2. Configure the build:

```shell
   cmake -B build -DCMAKE_INSTALL_PREFIX=~/build/install
```

3. Build and install:

```shell
   ninja install
```

#### Meson

Meson >= 1.10.0 is required. For more information, refer to
[Quick-guide](https://mesonbuild.com/Quick-guide.html)

```shell
   meson setup builddir 
   cd builddir 
   meson compile 
```

Then install the library using:

```shell
   meson install
```

#### Bazel

   Bazel is not yet supported. Please use [cmake](#cmake) or [meson](menson) instead.

## Testing

### CMake

### Meson

To run project tests:

```shell
   meson test 
```
### Bazel

   Bazel tests are not yet supported. Use [cmake](cmake) or [meson](menson) to run tests

## API documentation

### Data types

### `npio_size_t`
Alias for `size_t` used in APIs.

### `npio_bool_t`
Boolean type for npio, defined as `uint8_t`.

### `npio_uint16_t`
Unsigned 16‑bit integer type for npio.

`npio_int_t`
General integer type for npio.

```c
npio_status_t
```

Type for specifying an error or status code.

```c
npy_file_t
```

Low level NPY file descriptor.

> **Note:**  
> The `.npy` file format version is not equal to the NumPy Python package version.  
> It refers to the binary storage specification used inside the file (e.g. 1.0, 2.0, 3.0).

```c
typedef struct {
    FILE      *fp;
    npio_int_t version_major;
    npio_int_t version_minor;
    char       dtype[32];
    npio_int_t fortran_order;
    size_t     ndim;
    size_t     shape[NPY_ARRAY_DIM];
    size_t     header_len;
} npy_file_t;
```

`npy_shape_t`

Npy array shape type.

```c
      typedef struct {
          size_t shape[NPY_ARRAY_DIM];
          size_t ndim;
      } npy_shape_t;
```

`np_array_t`

Numpy array data descriptor.

```c
      typedef struct {
          char       *data;
          npy_shape_t shape;
          npio_size_t word_size;
          npio_bool_t fortran_order;
          npio_size_t num_vals;
      } np_array_t;
```

`npz_entry_t`
Array mapping in an NPZ archive.

```c
      typedef struct {
          char      *key;
          np_array_t value;
      } npz_entry_t;
```

`npz_t`

   NPZ file entries mapping.

```c

      typedef struct {
          npz_entry_t *entries;
          npio_size_t  count;
      } npz_t;
```

.. c:struct:: npy_file_t

   Low level NPY file descriptor.

```c
      typedef struct {
          FILE      *fp;
          npio_int_t version_major;
          npio_int_t version_minor;
          char       dtype[32];
          npio_int_t fortran_order;
          size_t     ndim;
          size_t     shape[NPY_ARRAY_DIM];
          size_t     header_len;
      } npy_file_t;
```

```c
void npio_strerror(npio_status_t statcode, char *buf, npio_size_t bufsize)
```

   Return a human readable string describing the specified error.

   :param statcode: The error code to get a string for.
   :param buf: A buffer to hold the error string.
   :param bufsize: Size of the buffer to hold the string.
   :return: The number of characters that would have been written to the buffer if it were large enough.
            If an encoding error occurs, a negative number is returned.

```c
npio_status_t npy_fread(npy_file_t *pnpy)
```

   Read and parse the header of a NumPy ``.npy`` file into a :c:type:`npy_file_t` structure.

   :param pnpy: Pointer to an :c:type:`npy_file_t` structure with an open file handle.
   :return: Status code indicating success or type of error.


#### `npio_status_t npy_fread(npy_file_t *pnpy)`

```c
npio_status_t npy_fread(npy_file_t *pnpy)
```

Read and parse the header of a NumPy `.npy` file into a `npy_file_t` structure.

- **pnpy**: Pointer to a `npy_file_t` structure with an open file handle.
- **Returns**: Status code indicating success or type of error.

#### `const char *npio_error_string(npio_status_t statcode)`

```c
const char *npio_error_string(npio_status_t statcode)
```

Convert a `npio_status_t` error code into a human readable string.

- **statcode**: The error code to convert.
- **Returns**: Pointer to a constant string describing the error. Returns `NULL` if the status code is not supported in the npio error list.

#### `void npio_error_printf(npio_status_t statcode)`

```c
void npio_error_printf(npio_status_t statcode)
```

Prints a human readable description of an npio error status.

- **statcode**: npio status code.
- **Returns**: None.

> **Note:** This function is mainly intended for debugging purposes.

#### `np_array_t *np_array_create(const npio_size_t *dims, npio_size_t ndim, npio_size_t word_size, npio_bool_t fortran_order)`

```c
np_array_t *np_array_create(const npio_size_t *dims, npio_size_t ndim, npio_size_t word_size, npio_bool_t fortran_order)
```

Allocator for a `np_array_t` object.

- **dims**: Array of `ndim` elements, each specifying the size of the array along one axis. All values must be greater than or equal to 1. Zero dimensions are not allowed in NumPy.
- **ndim**: Number of array dimensions. Must be greater than or equal to 1.
- **word_size**: The size in bytes of one element in the array.
- **fortran_order**: Array memory layout. NumPy usually defaults to 0 (C-order). If specified, nonzero indicates Fortran-order. Default in npio library is also 0.
- **Returns**: Pointer to the allocated `np_array_t` structure. Returns `NULL` if an invalid dimension value is provided or if `ndim` is zero.

> **Note:** This function performs validation of dimensions and will return a null pointer if the number of dimensions is zero or if any dimension size is invalid.


## Contributing

The project is under active development, and contributions are highly encouraged.If you are interested in collaborating, please feel free to fork the project and open a [pull request](https://github.com/wissem01chiha/npio/pulls) or contact the maintainer via [email](chihawissem08@gmail.com)

## License 

All material is provided under MIT License unless otherwise specified.

See the [LICENSE](LICENSE) file for more details

## Changelog


[Unreleased] - 2026-02-15
~~~~~~~~~~~~~~~~~~~~~~~~~

Added
^^^^^

- Added `cnpy <https://github.com/rogersce/cnpy>`__ library initial
  files 

Changed
^^^^^

Fixed
^^^^^
