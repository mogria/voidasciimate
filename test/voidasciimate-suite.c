#include "voidasciimate-suite.h"

void setup(void) {
}

void teardown(void) {
}

START_TEST (test_animate_fail) {
  fail("write some tests ... ");
} END_TEST

Suite *voidasciimate_suite(void) {
  // create suite
  Suite *s = suite_create("voidasciimate:");

  // create test case
  TCase *tc_class_index = tcase_create("animate");

  // test case has setup and teardown method
  tcase_add_checked_fixture(tc_class_index, setup, teardown);

  // add tests to test case
  tcase_add_test(tc_class_index, test_animate_fail);

  // add test case to suite
  suite_add_tcase(s, tc_class_index);
  return s;
}
