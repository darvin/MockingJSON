//
//  mocking_tests_helper.h
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#ifndef MockingJSON_mocking_tests_helper_h
#define MockingJSON_mocking_tests_helper_h

#include "tap.h"
#include "mocking_json.h"


typedef void (*TEST_func)();


#define TEST_CASE(TEST_CASE_NAME) \
    void test_case_##TEST_CASE_NAME() {\
        TEST_func *__test_functions = (TEST_func *)malloc(sizeof(TEST_func)*1024); \
        int __test_functions_count = 0;\
        note("===================\n   Case "#TEST_CASE_NAME);

#define END_TEST_CASE \
        for (int i=0; i<__test_functions_count; i++) { __test_functions[i](); }; \
    };

#define RUN_TEST_CASE(TEST_CASE_NAME) \
    test_case_##TEST_CASE_NAME();


#define TEST(TEST_NAME) \
    {struct currentTest { static void f(){ \
        note("-------------------\n   Test "#TEST_NAME); \

#define END_TEST \
    }}; \
    __test_functions[__test_functions_count] = &(currentTest::f); \
    __test_functions_count ++;}



#endif
