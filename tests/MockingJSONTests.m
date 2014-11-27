//
//  MockingJSONTests.m
//  MockingJSONTests
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>
#include "mocking_tests.h"
#include "mocking_conscell.h"
#include "mocking_sexpressions.h"

@interface MockingJSONTests : XCTestCase

@end

@implementation MockingJSONTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testSimpleProgram {
    XCTAssert(mocking_json_run("[\"+\", 2, 4]")==6, @"Pass");
}


- (void)testTests {
    XCTAssert(is_result_equal_to_expected_from_filename((void *)23, "blabla_(int)23.json"), @"int 23 should be ok");
    XCTAssert(is_result_equal_to_expected_from_filename((void *)23, "bla_bla_(int)23.json"), @"parsing sanity");
    XCTAssert(is_result_equal_to_expected_from_filename((void *)"some", "blabla_(char*)some.json"), @"char some should be ok");
}


- (void)testSExpressionsParsing {
    conscell *initial = sexpression_from_json_string("[1, 2, [3, 4], 5]");
    conscell *c = initial;
    XCTAssert(conscell_car_is_atom(c)&&((atom*)conscell_car(c))->longValue==1, @"first item should be correct");
    c = conscell_cdr(c);
    XCTAssert(conscell_car_is_atom(c)&&((atom*)conscell_car(c))->longValue==2, @"second item should be correct");
    c = conscell_cdr(c);
    XCTAssert(!conscell_car_is_atom(c), @"third item should be correct");
    conscell *internal = conscell_car(c);
    c = conscell_cdr(c);
    
    XCTAssert(conscell_car_is_atom(internal)&&((atom*)conscell_car(internal))->longValue==3, @"first item of internal should be correct");
    internal = conscell_cdr(internal);

    XCTAssert(conscell_car_is_atom(internal)&&((atom*)conscell_car(internal))->longValue==4, @"second item of internal should be correct");
    internal = conscell_cdr(internal);
    XCTAssert(internal==NULL, @"internal should have proper lenth");

    
    XCTAssert(conscell_car_is_atom(c)&&((atom*)conscell_car(c))->longValue==5, @"last item should be correct");

    c = conscell_cdr(c);
    XCTAssert(c==NULL, @"c should have proper lenth");
    
    
    conscell *c2 = sexpression_from_json_string("[1, [3, [33], 4], 6]");
    c2 = conscell_cdr(c2);
    c2 = conscell_cdr(c2);
    XCTAssert(conscell_car_is_atom(c2)&&((atom*)conscell_car(c2))->longValue==6, @"last item should be correct");

}

- (void)testSExpressionsSanity {
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
        XCTAssert(strcmp(expr, exprRev)==0, @"S expr %s should be correct, instead its %s", expr, exprRev);


    }
    
}

- (void)testProgs {
    
    NSString *progPath = [[[NSBundle bundleForClass:[self class]] resourcePath] stringByAppendingPathComponent:@"tests/progs"];
    
    NSArray *progsNames = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:progPath error:nil];
    for (NSString *progName in progsNames) {
        if ([[[progName pathExtension] lowercaseString] isEqualToString:@"json"] && ![progName hasPrefix:@"!"]) {
            bool result = mocking_test_filename([progName UTF8String]);
            
            XCTAssert(result==true, @"test %@ should pass", progName);
        }
    }
    
    
}



@end
