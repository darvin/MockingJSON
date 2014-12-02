//
//  mocking_vm.c
//  MockingJSON
//
//  Created by Sergey Klimov on 11/28/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include "mocking_vm.h"

/*
void vm_eval(call_frame *frame) {
}


cellValue vm_run_frame(call_frame *first_frame) {
    call_frame *f = first_frame;
    
    while (f->stack!=NULL) {
    
        while (true) {
            vm_expression exp = f->next;
            cellValue arg0, arg1, arg2, arg3;
            cell *currArg = exp.args;
            arg0 = cell_car_value(currArg);
            currArg = cell_cdr(currArg);
            arg1 = cell_car_value(currArg);
            currArg = cell_cdr(currArg);
            arg2 = cell_car_value(currArg);
            currArg = cell_cdr(currArg);
            arg3 = cell_car_value(currArg);
            
            switch (f->next.op) {
                case halt:
                    return f->acc;
                    break;
                case refer:
                    f->acc = vm_env_lookup(f->env, arg0.stringValue);
                    f->next = arg1.expValue;
                    break;
                case constant:
                    f->acc = arg0;
                    f->next = arg1.expValue;
                    break;
//                case close:
//                    vm_closure closure = vm_closure_new()
                case test:
                    if (!f->acc.doubleValue!=0) { //fixme type info
                        f->next = arg0.expValue;
                    } else {
                        f->next = arg1.expValue;
                    }
                    break;
                case assign:
                    vm_env_set(f->env, arg0.stringValue, f->acc);
                    frame->next = (vm_expression *)arg1;
                    break;
                case conti:
                    break;
                case nuate:
                    break;
                case frame:
                    break;
                case argument:
                    frame->rib = cell_new_atom(cell_new, <#cell *cdr#>)
                    break;
                case apply:
                    break;
            }

        }
        frame = frame->stack; //poping from stack
    }
    return frame->acc;
}
*/