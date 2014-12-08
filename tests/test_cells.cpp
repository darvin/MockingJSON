//
//  test_cells.cpp
//  MockingJSON
//
//  Created by Sergey Klimov on 12/7/14.
//  Copyright (c) 2014 Sergey Klimov. All rights reserved.
//

#include <stdio.h>
#include "mocking_tests_helper.h"
#include "mocking_json.h"

TEST_CASE(cells)

cellValue first;
first.longValue = 1;
cell *initial = cell_list(3, make_cell_car(make_cell_value_long(1), typeLong), make_cell_car(make_cell_value_long(2), typeLong),make_cell_car(make_cell_value_long(5), typeLong));
cell *c = initial;
ok(cell_car_type(c)==typeLong&&cell_car_value(c).longValue==1, "first item should be correct");
c = cell_cdr(c);
ok(cell_car_type(c)==typeLong&&cell_car_value(c).longValue==2, "second item should be correct");
c = cell_cdr(c);


ok(cell_car_type(c)==typeLong&&cell_car_value(c).longValue==5, "last item should be correct");

c = cell_cdr(c);
ok(c==NULL, "c should have proper lenth");

cell_destroy(initial);

TEST(CellList)


END_TEST



END_TEST_CASE
