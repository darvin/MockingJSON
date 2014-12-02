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
    c->car = value;
    c->type = type;
    c->cdr = cdr;
    return c;

}
cellValue cell_car_value(cell* c) {
    return c->car;
}
cellType cell_car_type(cell* c) {
    return c->type;
}

cell *cell_cdr(cell* cell) {
    return cell->cdr;
}

void cell_destroy(cell* cell) {
    if (cell->cdr!=NULL) {
        cell_destroy(cell->cdr);
    }
    switch (cell->type) {
        case typeString:
            free(cell->car.stringValue);
            break;
        case typeCell:
            cell_destroy(cell->car.cellValue);
            break;
        case typeNil:
        case typeLong:
        case typeDouble:
        default:
            break;
    }
}
