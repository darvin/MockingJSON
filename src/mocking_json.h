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

#include "mocking_conscell.h"
#include "mocking_sexpressions.h"


void *mocking_json_run(const char *prog);
void *mocking_json_run_filename(const char *filename);

#endif /* defined(__MockingJSON__mocking_json__) */
