//
//  mocking_compiler.h
//  MockingJSON
//
//  Created by Sergey Klimov on 12/7/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#ifndef __MockingJSON__mocking_compiler__
#define __MockingJSON__mocking_compiler__

#include <stdio.h>

#include "mocking_conscell.h"


cell *compile_code_to_vm(cell *);

vm_expression compile_code_to_vm_exp(cell *);


#endif /* defined(__MockingJSON__mocking_compiler__) */
