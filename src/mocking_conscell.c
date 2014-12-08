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
    c->car.value = value;
    c->car.type = type;
    c->cdr = cdr;
    return c;
}


cell * cell_list(int count, ...)
{
    va_list ap;
    int j;
    cell * result = NULL;

    va_start(ap, count);
    for (j = 0; j < count; j++) {
        cellCar car = va_arg(ap, cellCar);
        result = cell_cons(car.value, car.type, result);
    }
    va_end(ap);
    
    cell* curr = result;
    cell* reversed_cell = NULL;
    do {
        reversed_cell = cell_cons(cell_car_value(curr), cell_car_type(curr), reversed_cell);
    } while (((curr = cell_cdr(curr))));
    
//    cell_destroy(result);
    return reversed_cell;
}

void cell_extract(cell *c, int count, ...) {
    va_list ap;
    int j;
    cell *curr = c;
    
    va_start(ap, count);
    for (j = 0; j < count; j++) {
        cellCar *car = va_arg(ap, cellCar*);
        *car = cell_car(curr);
        
        curr = cell_cdr(curr);
    }
    va_end(ap);

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

bool cell_is_symbol(cell * cell) {
    return cell_cdr(cell) == NULL && cell_car_type(cell)==typeString;
}
bool cell_is_pair(cell * cell) {
    return cell_cdr(cell) != NULL;
}

void cell_destroy(cell* cell) {
    if (cell->cdr!=NULL) {
        cell_destroy(cell->cdr);
    }
    cell_car_destroy(cell->car);
}





const char *make_string_from_op(vm_op op){
    switch (op) {
        case refer: return "refer";
        case constant: return "constant";
        case test: return "test";
        case assign: return "assign";
        case conti: return "conti";
        case nuate: return "nuate";
        case frame: return "frame";
        case argument: return "argument";
        case apply: return "apply";
        case closure: return "closure";
        case ret: return "ret";
        case halt: return "halt";
        default: return "no-op";
    }
}



cellCar vLong(long v) {
    cellCar car;
    car.value.longValue = v;
    car.type = typeLong;
    return car;
}

cellCar vOp(vm_op v) {
    cellCar car;
    car.value.opValue = v;
    car.type = typeOp;
    return car;
}




cellCar vCell(cell* v) {
    cellCar car;
    car.value.cellValue = v;
    car.type = typeCell;
    return car;
}

cellCar vStr(const char *str) {
    cellCar car;
    car.value.stringValue = (char *)str;
    car.type = typeString;
    return car;
}

