//
//  test_parser.c
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include "mocking_tests_helper.h"

TEST_CASE(parser)

    
TEST(SExpressionsParsing)
    cell *initial = sexpression_from_json_string("[1, 2, [3, 4], 5]");
    cell *c = initial;
    ok(cell_car_type(c)==typeLong&&cell_car_value(c).longValue==1, "first item should be correct");
    c = cell_cdr(c);
    ok(cell_car_type(c)==typeLong&&cell_car_value(c).longValue==2, "second item should be correct");
    c = cell_cdr(c);
    ok(cell_car_type(c)==typeCell, "third item should be correct");
    cell *internal = cell_car_value(c).cellValue;
    c = cell_cdr(c);
    
    ok(cell_car_type(internal)==typeLong&&cell_car_value(internal).longValue==3, "first item of internal should be correct");
    internal = cell_cdr(internal);
    
    ok(cell_car_type(internal)==typeLong&&cell_car_value(internal).longValue==4, "second item of internal should be correct");
    internal = cell_cdr(internal);
    ok(internal==NULL, "internal should have proper lenth");
    
    
    ok(cell_car_type(c)==typeLong&&cell_car_value(c).longValue==5, "last item should be correct");
    
    c = cell_cdr(c);
    ok(c==NULL, "c should have proper lenth");
    
    cell_destroy(initial);

    cell *initial2 = sexpression_from_json_string("[1, [3, [335], 4], 6]");
    cell *c2 = initial2;

    c2 = cell_cdr(c2);
    c2 = cell_cdr(c2);
    ok(cell_car_type(c2)==typeLong&&cell_car_value(c2).longValue==6, "last item should be correct");
    cell_destroy(initial2);

    
END_TEST



TEST(SExpressionsParsingNULL)
    cell *initial = sexpression_from_json_string("[null, 5]");
    cell *c = initial;
    ok(cell_car_type(c)==typeNil, "something", "first item should be correct");
    cell_destroy(initial);
END_TEST

TEST(SExpressionsParsingBadJSONStrings)
    cell *initial = sexpression_from_json_string("[something, \"another\", 4, another2, 5]");
    cell *c = initial;
    is(cell_car_value(c).stringValue, "something", "first item should be correct");

    c = cell_cdr(c);
    is(cell_car_value(c).stringValue, "another", "2nd item should be correct");
    c = cell_cdr(c);
    ok(cell_car_type(c)==typeLong&&cell_car_value(c).longValue==4, "3rd item should be correct");
    c = cell_cdr(c);
    is(cell_car_value(c).stringValue, "another2", "4th item should be correct");
    c = cell_cdr(c);
    ok(cell_car_type(c)==typeLong&&cell_car_value(c).longValue==5, "4th item should be correct");
    cell_destroy(initial);
END_TEST



TEST(SExpressionsSanity)
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
        cell *c = sexpression_from_json_string(expr);
        const char *exprRev = sexpression_to_json_string(c);
        is(expr, exprRev, "Serialized expression have to be as deserialized");
        
        cell_destroy(c);
    }
    
END_TEST


XTEST(SExpressionsParsingHashExtension)
    cell *initial = sexpression_from_json_string("[4, {\"key\":\"value\", 5:9}, 6]");
    const char *exprRev = sexpression_to_json_string(initial);
    is(exprRev, "[4, [[\"key\", \"value\"], [5, 9]], 6]", "hash should be properly readed");
    cell_destroy(initial);


END_TEST



END_TEST_CASE
