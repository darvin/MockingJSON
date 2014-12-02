//
//  mocking_sexpressions.h
//  MockingJSON
//
//  Created by Sergey Klimov on 11/26/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#ifndef __MockingJSON__mocking_sexpressions__
#define __MockingJSON__mocking_sexpressions__

#include <stdio.h>

#include "mocking_conscell.h"

cell *sexpression_from_json_string(const char* string);
const char *sexpression_to_json_string(cell *exp);




#endif /* defined(__MockingJSON__mocking_sexpressions__) */
