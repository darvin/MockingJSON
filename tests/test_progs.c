//
//  test_progs.c
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include "mocking_tests_helper.h"

#include <string.h>



bool is_result_equal_to_expected_from_filename(void *result, const char *filename) {
    //fixme really bad parsing code
    
    char *typeNameStart = strstr(filename, "(") + 1;
    size_t typeNameSize = strstr(filename, ")") - typeNameStart;
    
    
    char *typeName = malloc(typeNameSize+1);
    
    strncpy(typeName, typeNameStart, typeNameSize);
    typeName[typeNameSize] = '\0';
    

    
    char *valueStart = typeNameStart + typeNameSize + 1;
    size_t valueSize = strstr(filename, ".json") - valueStart;
    
    char *valueStr = malloc(valueSize+1);
    
    strncpy(valueStr, valueStart, valueSize);
    valueStr[valueSize] = '\0';
    
    bool resultIsEqual = false;
    
    if (strcmp(typeName, "int")==0) {
        int exp = atoi(valueStr);
        resultIsEqual = exp==(int)result;
    } else if (strcmp(typeName, "char*")==0) {
        resultIsEqual = strcmp(result, valueStr)==0;
    } else if (strcmp(typeName, "void*")==0) {
        if (strcmp(valueStr, "NULL")==0) {
            resultIsEqual = result==NULL;
        }
    }
    
    
    
    
    free((void *)typeName);
    free((void *)valueStr);
    return resultIsEqual;
}

bool mocking_test_filename(const char *filename) {
    void *result = mocking_json_run_filename(filename);
    return is_result_equal_to_expected_from_filename(result, filename);
}





TEST_CASE(progs)
TEST(SimpleProgram) {
    todo();
    ok((int)mocking_json_run("[\"+\", 2, 4]")==6, "Pass");
    end_todo;
}


TEST(Tests) {
    ok(is_result_equal_to_expected_from_filename((void *)23, "blabla_(int)23.json"), "int 23 should be ok");
    ok(is_result_equal_to_expected_from_filename((void *)23, "bla_bla_(int)23.json"), "parsing sanity");
    ok(is_result_equal_to_expected_from_filename((void *)"some", "blabla_(char*)some.json"), "char some should be ok");
}



TEST(RunProgs) {
    /*
    NSString *progPath = [[[NSBundle bundleForClass:[self class]] resourcePath] stringByAppendingPathComponent:"tests/progs"];
    
    NSArray *progsNames = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:progPath error:nil];
    for (NSString *progName in progsNames) {
        if ([[[progName pathExtension] lowercaseString] isEqualToString:"json"] && ![progName hasPrefix:"!"]) {
            bool result = mocking_test_filename([progName UTF8String]);
            
            ok(result==true, "test %@ should pass", progName);
        }
    }*/
    
    
}



END_TEST_CASE