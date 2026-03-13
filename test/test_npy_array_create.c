#include "npio.h"
#include "unity.h"

void setUp(void) {
   
}

void tearDown(void) {
   
}


void test_npy_array_create_return_not_null(void) {

    // 3d array with shape (10,20,30)
    npio_size_t dims_arr[] = { 10, 20, 30 };   
    const npio_size_t *dims = dims_arr; 
    npio_size_t ndim = 2;  
    npio_size_t word_size = 1;
     npio_bool_t  fortran_order =false;
     npy_array_t* arr = npy_array_create(dims,ndim,
                            word_size,fortran_order);

    UNITY_TEST_ASSERT_NOT_NULL(arr,"","");
}

void test_npy_array_create_null_dims(void ){

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_npy_array_create_return_not_null);
    RUN_TEST(test_npy_array_create_null_dims);
    return UNITY_END();
}