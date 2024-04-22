#include "test.h"

START_TEST(s21_is_greater_test) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test2) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test3) {
  s21_decimal val1 = {{1, 0, 0, 0x00010000}};  // sign bit= 0 exponent= -1
  // 0.1
  s21_decimal val2 = {{10, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 10
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test4) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};

  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test5) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test6) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00010000}};

  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test7) {
  s21_decimal val1 = {{10000000, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 10000000
  s21_decimal val2 = {{10000000, 0, 0, 0x80000000}};  // sign bit= 1 exponent= 0
  // -10000000
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test8) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0x80000000}};

  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test9) {
  s21_decimal val1 = {{1, 0, 0, 0x000C0000}};  // sign bit= 0 exponent= -12
  // 1E-12
  s21_decimal val2 = {{1, 0, 0, 0x00100000}};  // sign bit= 0 exponent= -16
  // 1E-16
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test10) {
  s21_decimal val1 = {{1, 0, 0, 0x000C0000}};  // sign bit= 0 exponent= -12
  // 1E-12
  s21_decimal val2 = {{1, 0, 0, 0x000C0000}};  // sign bit= 0 exponent= -12
  // 1E-12
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

Suite *s21_is_greater_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("\033[34m \033[46m IS GREATER  \033[0m");
  tc = tcase_create("s21_is_greater");

  tcase_add_test(tc, s21_is_greater_test);
  tcase_add_test(tc, s21_is_greater_test2);
  tcase_add_test(tc, s21_is_greater_test3);
  tcase_add_test(tc, s21_is_greater_test4);
  tcase_add_test(tc, s21_is_greater_test5);
  tcase_add_test(tc, s21_is_greater_test6);
  tcase_add_test(tc, s21_is_greater_test7);
  tcase_add_test(tc, s21_is_greater_test8);
  tcase_add_test(tc, s21_is_greater_test9);
  tcase_add_test(tc, s21_is_greater_test10);
  suite_add_tcase(s, tc);
  return s;
}
