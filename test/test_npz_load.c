//Copyright (C) 2011  Carl Rogers
//Released under MIT License
//license available in LICENSE file, or at http://www.opensource.org/licenses/mit-license.php


#include "npio.h"
#include "unity.h"

// https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityGettingStartedGuide.md
void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}


void test_function_should_doBlahAndBlah(void) {
    //test stuff
}

void test_function_should_doAlsoDoBlah(void) {
    //more test stuff
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_doBlahAndBlah);
    RUN_TEST(test_function_should_doAlsoDoBlah);
    return UNITY_END();
}
