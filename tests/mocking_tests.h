//
//  mocking_tests.h
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#ifndef __MockingJSON__mocking_tests__
#define __MockingJSON__mocking_tests__

#include <stdio.h>
#include <stdbool.h>

bool mocking_test_filename(const char *filename);
bool is_result_equal_to_expected_from_filename(void *result, const char *filename);

#endif /* defined(__MockingJSON__mocking_tests__) */
