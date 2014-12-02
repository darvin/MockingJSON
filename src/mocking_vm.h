//
//  mocking_vm.h
//  MockingJSON
//
//  Created by Sergey Klimov on 11/28/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#ifndef __MockingJSON__mocking_vm__
#define __MockingJSON__mocking_vm__

#include <stdio.h>
#include "mocking_conscell.h"



typedef struct {
    cellValue acc;
    vm_expression next;
    cell *env;
    cell *rib;
    struct call_frame *stack;
} call_frame;



cellValue vm_run_frame(call_frame * frame);


#endif /* defined(__MockingJSON__mocking_vm__) */
