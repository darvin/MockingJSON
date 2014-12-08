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

TEST_CASE(compiler)


TEST(CompileSimple)
cell *prog = sexpression_from_json_string("[if, 4, four, not_four]");
const char *progRev = sexpression_to_json_string(prog);

cell *compiledProg = compile_code_to_vm(prog);
const char *progCompRev = sexpression_to_json_string(compiledProg);


END_TEST



END_TEST_CASE
