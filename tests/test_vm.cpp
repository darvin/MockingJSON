//
//  test_vm.cpp
//  MockingJSON
//
//  Created by Sergey Klimov on 11/28/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include <stdio.h>


//
//  test_compiler.cpp
//  MockingJSON
//
//  Created by Sergey Klimov on 12/7/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include <stdio.h>

#include "mocking_tests_helper.h"
#include "mocking_json.h"

TEST_CASE(vm)


TEST(quoteExp)
cell *prog = sexpression_from_json_string("[quote 4]");
cell *compiledProg = compile_code_to_vm(prog);


END_TEST

END_TEST_CASE
