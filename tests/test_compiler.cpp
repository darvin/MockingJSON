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
cell *prog = sexpression_from_json_string("[if, [quote 4], [quote four], [quote not_four]]");
const char *progRev = sexpression_to_json_string(prog);

cell *compiledProg = compile_code_to_vm(prog);
const char *progCompRev = sexpression_to_json_string(compiledProg);
printf("%s", progCompRev);


END_TEST

TEST(CompileMultiply)
const int mas_expressions = 2;
const char * expessions[] = {
"[if, [quote 4], [quote 5], [quote 6]]",
    "[<constant>, 4, [<test>, [<constant>, 5, [<halt>]], [<constant>, 6, [<halt>]]]]",
"[if, [quote null], [quote 5], [quote 6]]",
    "[<constant>, null, [<test>, [<constant>, 5, [<halt>]], [<constant>, 6, [<halt>]]]]",

};

for (int i=0; i<mas_expressions; i++) {
    const char *expr = expessions[i*2];
    cell *prog = sexpression_from_json_string(expr);
    cell *compiledProg = compile_code_to_vm(prog);
    const char *progCompRev = sexpression_to_json_string(compiledProg);
    is(progCompRev, expessions[i*2+1], "expression <%s> have to be properly compiled", expr);
    
    cell_destroy(prog);
    cell_destroy(compiledProg);
}



END_TEST

END_TEST_CASE
