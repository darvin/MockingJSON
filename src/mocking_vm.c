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

void *vm_exp_arg(vm_expression *exp, int index) {
    
}

void * vm_run_frame(call_frame *first_frame) {
    call_frame *frame = first_frame;
    
    while (frame->stack!=NULL) {
    
        while (true) {
            vm_expression *exp = frame->next;
            void * arg0 = vm_exp_arg(frame->next, 0);
            void * arg1 = vm_exp_arg(frame->next, 1);
            void * arg2 = vm_exp_arg(frame->next, 2);
            void * arg3 = vm_exp_arg(frame->next, 3);
            void * arg4 = vm_exp_arg(frame->next, 4);
            switch (frame->next->op) {
                case halt:
                    return frame->acc;
                    break;
                case refer:
                    frame->acc = vm_env_lookup(frame->env, (char *)arg0);
                    frame->next = (vm_expression *)arg1;
                    break;
                case constant:
                    frame->acc = vm_exp_arg(frame->next, 0);
                    frame->next = vm_exp_arg(frame->next, 1);
                    break;
//                case close:
//                    vm_closure closure = vm_closure_new()
                case test:
                    if (frame->acc) {
                        frame->next = arg0;
                    } else {
                        frame->next = arg1;
                    }
                    break;
                case assign:
                    frame->acc = vm_env_set(frame->env, (char *)arg0, frame->acc);
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