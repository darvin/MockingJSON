//
//  mocking_conscell.h
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#ifndef __MockingJSON__mocking_conscell__
#define __MockingJSON__mocking_conscell__

#include <stdio.h>
#include <stdbool.h>

typedef enum {
    atomNil,
    atomLong,
    atomDouble,
    atomString
} atomType;

typedef struct {
    double doubleValue;
    long longValue;
    char *stringValue;
    atomType type;
} atom;

typedef struct conscell
{
    atom *car_atom;
    struct conscell *car_conscell;
    struct conscell* cdr;
} conscell;

atom *atom_new(void *value, atomType type);
atom *atom_new_nil();
void atom_destroy(atom *atom);
conscell *conscell_new_conscell(conscell* car, conscell* cdr);
conscell *conscell_new_atom(atom* car, conscell* cdr);
void *conscell_car(conscell* cell);
bool conscell_car_is_atom(conscell* cell);
conscell *conscell_cdr(conscell* cell);
void conscell_destroy(conscell* cell);

#endif /* defined(__MockingJSON__mocking_conscell__) */
