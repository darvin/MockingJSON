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
    typeExp
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
    apply
} vm_op;

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
cell * cell_list(int count, ...);
cellValue cell_car_value(cell*);
cellType cell_car_type(cell*);

inline cellCar make_cell_car(cellValue value, cellType type) {
    cellCar car;
    car.value = value;
    car.type = type;
    return car;
}

inline cellValue make_cell_value_long(long v) {
    cellValue r;
    r.longValue = v;
    return r;
}


cell *cell_cdr(cell*);
cellCar cell_car(cell *c);
void cell_destroy(cell*);

#endif /* defined(__MockingJSON__mocking_cell__) */
