#include <check.h>

#include "s21_decimal.h"

START_TEST(div_0) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_3) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST
s21_decimal s21_decimal_get_min(void) {
  s21_decimal result = {{0x1, 0x0, 0x0, 0x1C0000}};

  return result;
}

s21_decimal s21_decimal_get_max(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  return result;
}

START_TEST(div_5) {
  int result;

  s21_decimal _a = s21_decimal_get_max();
  s21_decimal _b = s21_decimal_get_min();
  s21_decimal res;

  result = s21_div(_a, _b, &res);

  ck_assert_int_eq(result, 1);
}
END_TEST
// START_TEST(div_6) {
//   int result;

//   s21_decimal _a = s21_decimal_get_max();
//   s21_decimal _b = s21_decimal_get_min();
//   s21_decimal res;

//   result = s21_div(_b, _a, &res);

//   ck_assert_int_eq(result, 1);
// }
// END_TEST

int run_s21_div() {
  Suite *s = suite_create("\033[45m-=s21_div=-\033[0m");
  TCase *tc = tcase_create("case_div");

  SRunner *srunner = srunner_create(s);

  int result;

  suite_add_tcase(s, tc);
  tcase_add_test(tc, div_0);
  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_5);
  //   tcase_add_test(tc, div_6);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}