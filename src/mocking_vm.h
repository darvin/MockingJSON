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


typedef struct call_frame call_frame;
struct call_frame{
    cellCar acc;
    vm_expression next;
    cell *env;
    cell *rib;
    call_frame *stack;
};



cellCar vm_run_frame(call_frame *);


#endif /* defined(__MockingJSON__mocking_vm__) */
