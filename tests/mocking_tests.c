//
//  mocking_tests.c
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//





#include "mocking_tests_helper.h"


int main () {
    RUN_TEST_CASE(parser);
    RUN_TEST_CASE(progs);
    done_testing();
}




