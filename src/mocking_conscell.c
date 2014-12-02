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



cell *cell_cons(cellValue value, cellType type, cell* cdr) {
    cell *c = malloc(sizeof(cell));
    c->car.value = value;
    c->car.type = type;
    c->cdr = cdr;
    return c;

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
