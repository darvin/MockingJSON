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
    typeCell,
    typeExp,
    typeOp
} cellType;




typedef enum {
    halt = 0,
    refer,
    constant,
    test,
    assign,
    conti,
    nuate,
    frame,
    argument,
    closure,
    apply,
    ret
} vm_op;

const char *make_string_from_op(vm_op op);
vm_op make_op_from_string(const char *string);

typedef struct vm_expression vm_expression;
typedef struct cell cell;
struct vm_expression{
    vm_op op;
    struct cell *args;
};

typedef union {
    double doubleValue;
    long longValue;
    char *stringValue;
    struct cell *cellValue;
    vm_expression expValue;
    vm_op opValue;
} cellValue;

typedef struct {
    cellValue value;
    cellType type;
} cellCar;

typedef struct cell
{
    cellCar car;
    struct cell* cdr;
} cell;

cell *cell_cons(cellValue, cellType, cell*);
cell *cell_list(int count, ...);
void cell_extract(cell *, int count, ...);

cellValue cell_car_value(cell*);
cellType cell_car_type(cell*);

cellCar vLong(long);

cellCar vOp(vm_op);

cellCar vCell(cell* );

cellCar vStr(const char*);

bool cell_is_symbol(cell *);
bool cell_is_pair(cell *);

cell *cell_cdr(cell*);
cellCar cell_car(cell *c);
void cell_destroy(cell*);

#endif /* defined(__MockingJSON__mocking_cell__) */
