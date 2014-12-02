//
//  mocking_cell.h
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#ifndef __MockingJSON__mocking_cell__
#define __MockingJSON__mocking_cell__

#include <stdio.h>
#include <stdbool.h>

typedef enum {
    typeNil = 0,
    typeLong,
    typeDouble,
    typeString,
    typeCell
} cellType;


typedef union {
    double doubleValue;
    long longValue;
    char *stringValue;
    struct cell *cellValue;
} cellValue;

typedef struct cell
{
    cellValue car;
    cellType type;
    struct cell* cdr;
} cell;

cell *cell_cons(cellValue, cellType, cell*);
cellValue cell_car_value(cell*);
cellType cell_car_type(cell*);
cell *cell_cdr(cell*);
void cell_destroy(cell*);

#endif /* defined(__MockingJSON__mocking_cell__) */
