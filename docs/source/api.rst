.. _api:

API documentation
=================


Data types
----------

.. c:type:: npio_status_t

    Type for specifying an error or status code.

.. c:type:: npio_size_t

.. c:type:: npio_bool_t

.. c:type:: npio_uint16_t

.. c:type:: npy_shape_t

.. c:type:: np_array_t

    .. code:: c

        typedef struct {
            char *data;   
            npy_shape_t shape;        
            npio_size_t word_size;
            npio_bool_t fortran_order;
            npio_size_t num_vals;
        } np_array_t;

API
---


.. c:function:: void npio_strerror(npio_status_t statcode, char *buf, npio_size_t bufsize)

        Return a human readable string describing the specified error.