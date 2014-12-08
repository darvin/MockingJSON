//
//  mocking_compiler.c
//  MockingJSON
//
//  Created by Sergey Klimov on 12/7/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include "mocking_compiler.h"

#include <string.h>

cell *__compile_exp_to_vm_assembly(cell *x, cell* next) {
    
    if (next==NULL) {
        next = cell_list(1, vOp(halt));
    }
    
    if (cell_is_symbol(x)) {
        return cell_list(3, vOp(refer), vCell(x), vCell(next));
    } else if (cell_is_pair(x)) {
        const char *exp = cell_car(x).value.stringValue;
        cell *args = cell_cdr(x);
        
        
        
        if (strcmp(exp, "quote")==0) {
            cellCar obj;
            cell_extract(args, 1, &obj);
            return cell_list(3, vOp(constant), obj, vCell(next));
        } else if (strcmp(exp, "lambda")==0) {
            cellCar vars, body;
            cell_extract(args, 2, &vars, &body);

            return cell_list(3, vOp(closure), vars, __compile_exp_to_vm_assembly(body   .value.cellValue, cell_list(1, vOp(ret))), next);

        } else if (strcmp(exp, "if")==0) {
            cellCar test_, then_, else_;
            cell_extract(args, 3, &test_, &then_, &else_);

            
            
            cell *thenc = __compile_exp_to_vm_assembly(then_.value.cellValue, next);
            cell *elsec = __compile_exp_to_vm_assembly(else_.value.cellValue, next);
            return __compile_exp_to_vm_assembly(test_.value.cellValue, cell_list(3, vOp(test), vCell(thenc), vCell(elsec)));
        } else if (strcmp(exp, "set!")==0) {
            cellCar var, exptoset;
            cell_extract(args, 2, &var, &exptoset);

            return __compile_exp_to_vm_assembly(exptoset.value.cellValue, cell_list(3, vOp(assign), var, next));

        } else if (strcmp(exp, "call/cc")==0) {
            ///
        } else {
            /// todo
        }


    } else {
        return cell_list(3, vOp(constant), vCell(x), vCell(next));
    }
    
    return NULL;
}

cell *compile_code_to_vm(cell *prog) {
    

    return __compile_exp_to_vm_assembly(prog, NULL);
    
}

vm_expression compile_code_to_vm_exp(cell *);
