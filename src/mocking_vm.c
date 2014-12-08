//
//  mocking_vm.c
//  MockingJSON
//
//  Created by Sergey Klimov on 11/28/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include "mocking_vm.h"
#include "mocking_conscell.h"

void vm_eval(call_frame *frame) {
}


cellCar vm_env_lookup(cell *env, char* var_name) {
    cellCar result;
    return result;
}

void vm_env_set(cell *env, char* var_name, cellCar var_value) {
    
}

cellCar vm_run_frame(call_frame *first_frame) {
    call_frame *f = first_frame;
    
    while (f->stack!=NULL) {
    
        while (true) {
            vm_expression exp = f->next;
            cellCar arg0, arg1, arg2, arg3;
            cell *currArg = exp.args;
            arg0 = cell_car(currArg);
            currArg = cell_cdr(currArg);
            arg1 = cell_car(currArg);
            currArg = cell_cdr(currArg);
            arg2 = cell_car(currArg);
            currArg = cell_cdr(currArg);
            arg3 = cell_car(currArg);
            
            switch (f->next.op) {
                case halt:
                    return f->acc;
                    break;
                case refer:
                    f->acc = vm_env_lookup(f->env, arg0.value.stringValue);
                    f->next = arg1.value.expValue;
                    break;
                case constant:
                    f->acc = arg0;
                    f->next = arg1.value.expValue;
                    break;
//                case close:
//                    vm_closure closure = vm_closure_new()
                case test:
                    if (f->acc.type!=typeNil) {
                        f->next = arg0.value.expValue;
                    } else {
                        f->next = arg1.value.expValue;
                    }
                    break;
                case assign:
                    vm_env_set(f->env, arg0.value.stringValue, f->acc);
                    f->next = arg1.value.expValue;
                    break;
                case conti:
                    break;
                case nuate:
                    break;
                case frame:
                    break;
                case argument:
                    f->rib = cell_cons(f->acc.value, f->acc.type, f->rib);
                    f->next = arg1.value.expValue;
                    break;
                case apply:
                    f = (call_frame *)f->stack; //?
                    break;
            }

        }
        f = f->stack; //poping from stack
    }
    return f->acc;
}
