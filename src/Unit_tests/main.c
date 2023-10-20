#include "test.h"

int main(void) {
  int failed = 0;
  Suite *SmartCalc[] = {
      General_test(),     Dot_validation(), Brackets_validation(),
      Whole_validation(), Credit(),         NULL};
  for (int i = 0; SmartCalc[i] != NULL; i++) {
    SRunner *sr = srunner_create(SmartCalc[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);
  return 0;
}