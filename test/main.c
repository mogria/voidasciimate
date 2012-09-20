#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "voidasciimate-suite.h"


int main(int argc, char *argv[]) {
  int number_failed;

  Suite *s = voidasciimate_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
