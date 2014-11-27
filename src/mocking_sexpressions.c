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


atom *atom_from_json_token(jsmntok_t token,  const char* json_string) {
    size_t valueSize = token.end - token.start;
    char * valueBuff = malloc(valueSize +1);
    strncpy(valueBuff, json_string + token.start, valueSize);
    valueBuff[valueSize] = '\0';
    
    atom *atom = NULL;
//    printf("PROCESSING ATOM %s length %d\n", valueBuff, token.end - token.start);
    
    char* p = valueBuff;
    double val;
    switch (token.type) {
        case JSMN_PRIMITIVE:
            errno = 0;
            val = strtod(valueBuff, &p);
            if (errno != 0 || valueBuff == p || *p != 0)
                atom = atom_new_nil();
            if (floor(val)==val) {
                long longValue = (long)val;
                atom = atom_new(&longValue, atomLong);
                
            }
            else {
                atom = atom_new(&val, atomDouble);
            }
            break;
        case JSMN_STRING:
            return atom_new(valueBuff, atomString);
            break;
            
        default:
            break;
    }
    free((void*)valueBuff);
    
    return atom;
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
        conscell *cell = NULL;

        while (j<=token.size) {
            int child_json_element_size;
            jsmntok_t *next_tokens = t+j+child_elements_size;
            
            
            if (next_tokens[0].type == JSMN_ARRAY) {
                conscell *c = sexpression_from_json_token(next_tokens, json_string, &child_json_element_size);
                child_elements_size += child_json_element_size;
            
                cell = conscell_new_conscell(c, cell);
            } else {
                atom *a = atom_from_json_token(next_tokens[0], json_string);
                cell = conscell_new_atom(a, cell);
            }
            j ++;

        }
        *json_element_size += child_elements_size;
        conscell* curr = cell;
        conscell* reversed_cell = NULL;
        do {
            if (conscell_car_is_atom(curr)) {
                reversed_cell = conscell_new_atom(conscell_car(curr), reversed_cell);

            } else {
                reversed_cell = conscell_new_conscell(conscell_car(curr), reversed_cell);

            }
        } while (((curr = conscell_cdr(curr))));
        return reversed_cell;
    }

    
    return NULL;

}

conscell *sexpression_from_json_string(const char* json_string) {
    int i;
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




const char *sexpression_to_json_string(conscell *exp) {
    char * res = malloc(1024);
    sprintf(res, "[");

    while (exp) {
        if (conscell_car_is_atom(exp)) {
            atom * a = conscell_car(exp);
            switch (a->type) {
                case atomDouble:
                    sprintf(res+strlen(res), "%g", a->doubleValue);
                    break;
                case atomLong:
                    sprintf(res+strlen(res), "%ld", a->longValue);
                    break;
                case atomNil:
                    sprintf(res+strlen(res), "null");
                    break;
                case atomString:
                    sprintf(res+strlen(res), "\"%s\"", a->stringValue);
                    break;

                default:
                    break;
            }
        } else {
            const char * resChild = sexpression_to_json_string(conscell_car(exp));
            sprintf(res+strlen(res), "%s", resChild);
            free(resChild);
        }
        
        exp = conscell_cdr(exp);
        if (exp) {
            sprintf(res+strlen(res), ", ");
        }
    }
    
    sprintf(res+strlen(res), "]");

    return res;
}