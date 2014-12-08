//
//  mocking_json.h
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#ifndef __MockingJSON__mocking_json__
#define __MockingJSON__mocking_json__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "mocking_conscell.h"
#include "mocking_sexpressions.h"
#include "mocking_vm.h"
#include "mocking_compiler.h"

void *mocking_json_run(const char *prog);
void *mocking_json_run_filename(const char *filename);


#ifdef __cplusplus
}
#endif
    
#endif /* defined(__MockingJSON__mocking_json__) */
