//
//  mocking_tests_helper.h
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#ifndef MockingJSON_mocking_tests_helper_h
#define MockingJSON_mocking_tests_helper_h

#include <tap.h>
#include "mocking_json.h"

#define TEST_CASE(TEST_CASE_NAME) \
    void test_##TEST_CASE_NAME(){ \
    note("===================\n   Case "#TEST_CASE_NAME);

#define END_TEST_CASE }

#define RUN_TEST_CASE(TEST_CASE_NAME) \
    extern void test_##TEST_CASE_NAME(); \
    test_##TEST_CASE_NAME();


#define TEST(TEST_NAME) \
    note("-------------------\n   Test "#TEST_NAME);



#endif
