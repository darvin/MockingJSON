//
//  mocking_cell.c
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include "mocking_conscell.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>




cell *cell_cons(cellValue value, cellType type, cell* cdr) {
    cell *c = malloc(sizeof(cell));
    c->car = make_cell_car(value, type);
    c->cdr = cdr;
    return c;
}


cell * cell_list(int count, ...)
{
    va_list ap;
    int j;
    cell * result = NULL;
    printf("LIST %d\n", count);

    va_start(ap, count);
    for (j = 0; j < count; j++) {
        cellCar car = va_arg(ap, cellCar);
        printf("LIST %ld\n", car.value.longValue);
        result = cell_cons(car.value, car.type, result);
    }
    va_end(ap);
    
    cell* curr = result;
    cell* reversed_cell = NULL;
    do {
        reversed_cell = cell_cons(cell_car_value(curr), cell_car_type(curr), reversed_cell);
    } while (((curr = cell_cdr(curr))));
    return reversed_cell;

}

cellValue cell_car_value(cell* c) {
    return c->car.value;
}
cellType cell_car_type(cell* c) {
    return c->car.type;
}

cellCar cell_car(cell *c) {
    return c->car;
}

cell *cell_cdr(cell* cell) {
    return cell->cdr;
}

void cell_car_destroy(cellCar car) {
    switch (car.type) {
        case typeString:
            free(car.value.stringValue);
            break;
        case typeCell:
            cell_destroy(car.value.cellValue);
            break;
        case typeNil:
        case typeLong:
        case typeDouble:
        default:
            break;
    }

}

void cell_destroy(cell* cell) {
    if (cell->cdr!=NULL) {
        cell_destroy(cell->cdr);
    }
    cell_car_destroy(cell->car);
}
