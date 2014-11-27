//
//  test_parser.c
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include "mocking_tests_helper.h"

TEST_CASE(parser)

    
TEST(SExpressionsParsing) {
    conscell *initial = sexpression_from_json_string("[1, 2, [3, 4], 5]");
    conscell *c = initial;
    ok(conscell_car_is_atom(c)&&((atom*)conscell_car(c))->longValue==1, "first item should be correct");
    c = conscell_cdr(c);
    ok(conscell_car_is_atom(c)&&((atom*)conscell_car(c))->longValue==2, "second item should be correct");
    c = conscell_cdr(c);
    ok(!conscell_car_is_atom(c), "third item should be correct");
    conscell *internal = conscell_car(c);
    c = conscell_cdr(c);
    
    ok(conscell_car_is_atom(internal)&&((atom*)conscell_car(internal))->longValue==3, "first item of internal should be correct");
    internal = conscell_cdr(internal);
    
    ok(conscell_car_is_atom(internal)&&((atom*)conscell_car(internal))->longValue==4, "second item of internal should be correct");
    internal = conscell_cdr(internal);
    ok(internal==NULL, "internal should have proper lenth");
    
    
    ok(conscell_car_is_atom(c)&&((atom*)conscell_car(c))->longValue==5, "last item should be correct");
    
    c = conscell_cdr(c);
    ok(c==NULL, "c should have proper lenth");
    
    
    conscell *c2 = sexpression_from_json_string("[1, [3, [335], 4], 6]");
    c2 = conscell_cdr(c2);
    c2 = conscell_cdr(c2);
    ok(conscell_car_is_atom(c2)&&((atom*)conscell_car(c2))->longValue==6, "last item should be correct");
    
}

TEST(SExpressionsSanity) {
    int maxExpr = 9;
    const char * expessions[] = {
        "[1, 2]",
        "[1, 2.05]",
        "[1, 2.05, 5]",
        "[1, \"something\", 5]",
        "[1, 2, [3, 4]]",
        "[1, 2, [3, 4], 6]",
        "[1, [3, [33], 4], 6]",
        "[1, [3, [33, \"some\"], 4], 6]",
        "[[\"anything\"], 1, [3, [33, \"some\"], 4], 6]",
        
    };
    for (int i=0; i<maxExpr; i++) {
        const char *expr = expessions[i];
        conscell *c = sexpression_from_json_string(expr);
        char *exprRev = sexpression_to_json_string(c);
        is(expr, exprRev, "Serialized expression have to be as deserialized");
        
        
    }
    
}


END_TEST_CASE