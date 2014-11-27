//
//  mocking_tests.c
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include "mocking_tests.h"
#include "mocking_json.h"
#include <stdlib.h>
#include <string.h>

bool is_result_equal_to_expected_from_filename(void *result, const char *filename) {
    //fixme really bad parsing code

    char *typeNameStart = strstr(filename, "(") + 1;
    size_t typeNameSize = strstr(filename, ")") - typeNameStart;
    
    
    char *typeName = malloc(typeNameSize);

    strncpy(typeName, typeNameStart, typeNameSize);
    
    
    char *valueStart = typeNameStart + typeNameSize + 1;
    size_t valueSize = strstr(filename, ".json") - valueStart;
    
    char *valueStr = malloc(valueSize);

    strncpy(valueStr, valueStart, valueSize);

    
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




