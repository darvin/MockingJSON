//
//  mocking_sexpressions.c
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include "mocking_sexpressions.h"

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsmn.h"


cellValue atom_from_json_token(jsmntok_t token,  const char* json_string, cellType *type) {
    size_t valueSize = token.end - token.start;
    char * valueBuff = malloc(valueSize +1);
    strncpy(valueBuff, json_string + token.start, valueSize);
    valueBuff[valueSize] = '\0';
    
//    printf("PROCESSING ATOM %s length %d\n", valueBuff, token.end - token.start);
    cellValue result;
    
    char* p = valueBuff;
    double val;
    switch (token.type) {
        case JSMN_PRIMITIVE:
            errno = 0;
            val = strtod(valueBuff, &p);
            if (errno != 0 || valueBuff == p || *p != 0) {
                //this case its "primitive string", a unquoted string allowed by non-string mode of JSMN
                //this is the case for unquoted "null" too
                if (strcmp(valueBuff, "null")==0) {
                    *type = typeNil;
                } else {
                    result.stringValue = malloc(strlen(valueBuff)+1);
                    strncpy(result.stringValue, valueBuff, strlen(valueBuff));
                    result.stringValue[strlen(valueBuff)] = '\0';
                    *type = typeString;
                }
            } else if (floorl(val)==val) {
                result.longValue = (long)val;
                *type = typeLong;
                
            }
            else {
                result.doubleValue = val;
                *type = typeDouble;
            }
            break;
        case JSMN_STRING:
            result.stringValue = malloc(strlen(valueBuff)+1);
            strncpy(result.stringValue, valueBuff, strlen(valueBuff));
            result.stringValue[strlen(valueBuff)] = '\0';
            *type = typeString;
            break;
            
        default:
            break;
    }
    free((void*)valueBuff);
    
    return result;
}

void *sexpression_from_json_token(jsmntok_t t[1024], const char* json_string, int *json_element_size) {
    
    jsmntok_t token = t[0];
    if (token.type != JSMN_ARRAY) {
        printf("ERROR in parsing!");
        return NULL;
    }

    if (token.type == JSMN_ARRAY) {
        *json_element_size = token.size;
        
//        char * valueBuff = malloc(token.end - token.start+1);
//        strlcpy(valueBuff, json_string + token.start, token.end - token.start+1);
//        printf("PROCESSING array %s  \n", valueBuff);

        int j = 1;
        int child_elements_size =0;
        cell *c = NULL;

        while (j<=token.size) {
            int child_json_element_size;
            jsmntok_t *next_tokens = t+j+child_elements_size;
            
            
            if (next_tokens[0].type == JSMN_ARRAY) {
                cell *child = sexpression_from_json_token(next_tokens, json_string, &child_json_element_size);
                child_elements_size += child_json_element_size;
                cellValue cellv;
                cellv.cellValue = child;
                c = cell_cons(cellv, typeCell, c);
            } else {
                cellType type = typeNil;
                cellValue a = atom_from_json_token(next_tokens[0], json_string, &type);
                c = cell_cons(a, type, c);
            }
            j ++;

        }
        *json_element_size += child_elements_size;
        cell* curr = c;
        cell* reversed_cell = NULL;
        do {
            reversed_cell = cell_cons(cell_car_value(curr), cell_car_type(curr), reversed_cell);
        } while (((curr = cell_cdr(curr))));
        return reversed_cell;
    }

    
    return NULL;

}

cell *sexpression_from_json_string(const char* json_string) {
    int r;
    jsmn_parser p;
    jsmntok_t t[1024];
    
    jsmn_init(&p);
    r = jsmn_parse(&p, json_string, strlen(json_string), t, sizeof(t)/sizeof(t[0]));
    if (r < 0) {
        printf("Failed to parse JSON: %d\n", r);
        return NULL;
    }
    
    if (r < 1 || t[0].type != JSMN_ARRAY) {
        printf("Array expected\n");
        return NULL;
    }
    int json_element_size;
    return sexpression_from_json_token(t, json_string, &json_element_size);
  
}




const char *sexpression_to_json_string(cell *exp) {
    char * res = malloc(1024);
    sprintf(res, "[");
    const char * resChild;
    while (exp) {
        cellValue value = cell_car_value(exp);
        switch (cell_car_type(exp)) {
            case typeDouble:
                sprintf(res+strlen(res), "%g", value.doubleValue);
                break;
            case typeLong:
                sprintf(res+strlen(res), "%ld", value.longValue);
                break;
            case typeNil:
                sprintf(res+strlen(res), "null");
                break;
            case typeString:
                sprintf(res+strlen(res), "\"%s\"", value.stringValue);
                break;
            case typeCell:
                
                resChild = sexpression_to_json_string(value.cellValue);
                sprintf(res+strlen(res), "%s", resChild);
                free((void *)resChild);

                break;
            case typeOp:
                sprintf(res+strlen(res), "<%s>", make_string_from_op(value.opValue));
                break;

            default:
                break;
        }
        
        exp = cell_cdr(exp);
        if (exp) {
            sprintf(res+strlen(res), ", ");
        }
    }
    
    sprintf(res+strlen(res), "]");

    return res;
}
