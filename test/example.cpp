//Copyright (C) 2011  Carl Rogers
//Released under MIT License
//license available in LICENSE file, or at http://www.opensource.org/licenses/mit-license.php

#include "npio.h"
#include <complex>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <gtest/gtest.h>

const int Nx = 128;
const int Ny = 64;
const int Nz = 32;

class NpyIoTest : public ::testing::Test {
protected:
    std::vector<std::complex<double>> data;

    void SetUp() override {
        srand(0);
        data.resize(Nx * Ny * Nz);
        for (int i = 0; i < Nx * Ny * Nz; i++) {
            data[i] = std::complex<double>(rand(), rand());
        }
    }
};

TEST_F(NpyIoTest, SaveAndLoadNpy) {
    npy_save("arr1.npy", &data[0], {Nz, Ny, Nx}, "w");

    NpyArray arr = npy_load("arr1.npy");
    std::complex<double>* loaded_data = arr.data<std::complex<double>>();

    EXPECT_EQ(arr.word_size, sizeof(std::complex<double>));
    ASSERT_EQ(arr.shape.size(), 3u);
    EXPECT_EQ(arr.shape[0], Nz);
    EXPECT_EQ(arr.shape[1], Ny);
    EXPECT_EQ(arr.shape[2], Nx);

    for (int i = 0; i < Nx * Ny * Nz; i++) {
        EXPECT_EQ(data[i], loaded_data[i]);
    }
}

TEST_F(NpyIoTest, AppendToNpy) {
    npy_save("arr1.npy", &data[0], {Nz, Ny, Nx}, "w");
    npy_save("arr1.npy", &data[0], {Nz, Ny, Nx}, "a");

    NpyArray arr = npy_load("arr1.npy");
    ASSERT_EQ(arr.shape.size(), 3u);
    EXPECT_EQ(arr.shape[0], 2 * Nz); // appended along first dimension
    EXPECT_EQ(arr.shape[1], Ny);
    EXPECT_EQ(arr.shape[2], Nx);
}

TEST_F(NpyIoTest, SaveAndLoadNpz) {
    double myVar1 = 1.2;
    char myVar2 = 'a';

    npz_save("out.npz", "myVar1", &myVar1, {1}, "w");
    npz_save("out.npz", "myVar2", &myVar2, {1}, "a");
    npz_save("out.npz", "arr1", &data[0], {Nz, Ny, Nx}, "a");

    NpyArray arr2 = npz_load("out.npz", "arr1");
    EXPECT_EQ(arr2.shape.size(), 3u);
    EXPECT_EQ(arr2.shape[0], Nz);
    EXPECT_EQ(arr2.shape[1], Ny);
    EXPECT_EQ(arr2.shape[2], Nx);

    npz_t my_npz = npz_load("out.npz");
    NpyArray arr_mv1 = my_npz["myVar1"];
    double* mv1 = arr_mv1.data<double>();

    ASSERT_EQ(arr_mv1.shape.size(), 1u);
    EXPECT_EQ(arr_mv1.shape[0], 1);
    EXPECT_DOUBLE_EQ(mv1[0], myVar1);
}
