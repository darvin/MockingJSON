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


TEST(CellList)

cell *initial = cell_list(3, vLong(1), vLong(2),  vLong(5));
cell *c = initial;
ok(cell_car_type(c)==typeLong&&cell_car_value(c).longValue==1, "first item should be correct");
c = cell_cdr(c);
ok(cell_car_type(c)==typeLong&&cell_car_value(c).longValue==2, "second item should be correct");
c = cell_cdr(c);


ok(cell_car_type(c)==typeLong&&cell_car_value(c).longValue==5, "last item should be correct");

c = cell_cdr(c);
ok(c==NULL, "c should have proper lenth");

cell_destroy(initial);

END_TEST



TEST(CellList)

cell *initial = cell_list(3, vLong(1), vLong(2),  vLong(5));


cellCar c1, c2, c3;

cell_extract(initial, 3, &c1, &c2, &c3);

ok(c1.type==typeLong&&c1.value.longValue==1, "first item should be correct");

ok(c2.type==typeLong&&c2.value.longValue==2, "second item should be correct");
ok(c3.type==typeLong&&c3.value.longValue==5, "last item should be correct");


cell_destroy(initial);

END_TEST


END_TEST_CASE
