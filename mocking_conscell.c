//
//  mocking_conscell.c
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include "mocking_conscell.h"
#include <stdlib.h>
#include <string.h>

conscell *conscell_new_atom(atom* car, conscell* cdr) {
    conscell *c = malloc(sizeof(conscell));
    c->car_atom = car;
    c->cdr = cdr;
    return c;
}

conscell *conscell_new_conscell(conscell* car, conscell* cdr) {
    conscell *c = malloc(sizeof(conscell));
    c->car_conscell = car;
    c->cdr = cdr;
    return c;
}

void *conscell_car(conscell* cell) {
    if (cell->car_atom != NULL) {
        return cell->car_atom;
    } else {
        return cell->car_conscell;
    }
}
bool conscell_car_is_atom(conscell* cell) {
    return cell->car_atom!=NULL;
}
conscell *conscell_cdr(conscell* cell) {
    return cell->cdr;
}

void conscell_destroy(conscell* cell) {
    conscell_destroy(cell->cdr);
    if (cell->car_atom==NULL) {
        conscell_destroy(cell->car_conscell);
    } else {
        atom_destroy(cell->car_atom);
    }
}

atom *atom_new_nil(){
    atom *a = malloc(sizeof(atom));
    a->type = atomNil;
    return a;
}

atom *atom_new(void *value, atomType type) {
    atom *a = malloc(sizeof(atom));
    a->type = type;
    switch (a->type) {
        case atomLong:
            a->longValue = *(long*)value;
            break;
        case atomDouble:
            a->doubleValue  = *(double*)value;
            break;
        case atomNil:
            break;
        case atomString:
            a->stringValue = malloc(strlen(value));
            strncpy(a->stringValue, value, strlen(value));
            break;
        default:
            break;
    }
    return a;
}
void atom_destroy(atom *atom) {
    switch (atom->type) {
        case atomLong:
            break;
        case atomDouble:
            break;
        case atomNil:
            break;
        case atomString:
            free((void*)atom->stringValue);
            break;
        default:
            break;
    }
}
