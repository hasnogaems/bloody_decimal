#include "test.h"

START_TEST(s21_is_less_test) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test2) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test3) {
  s21_decimal val1 = {{0, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 0
  s21_decimal val2 = {{0, 0, 0, 0x80000000}};  // sign bit= 1 exponent= 0
  // -0
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test4) {
  s21_decimal val1 = {{1234567, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 1234567
  s21_decimal val2 = {{1234567, 0, 0, 0x00030000}};  // sign bit= 0 exponent= -3
  // 1234.567
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test5) {
  s21_decimal val1 = {{1, 0, 0, 0x00010000}};  // sign bit= 0 exponent= -1
  // 0.1
  s21_decimal val2 = {{10, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 10
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test6) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};

  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test7) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test8) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00010000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test9) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};

  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test10) {
  s21_decimal val1 = {{1, 0, 0, 0x80000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};

  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test11) {
  s21_decimal val2 = {{0, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 0
  s21_decimal val1 = {{1, 0, 0, 0x80000000}};  // sign bit= 0 exponent= 0
  // -1
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

Suite *s21_is_less_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("\033[34m \033[46m IS LESS TESTS \033[0m");
  tc = tcase_create("s21_is_less");

  tcase_add_test(tc, s21_is_less_test);
  tcase_add_test(tc, s21_is_less_test2);
  tcase_add_test(tc, s21_is_less_test3);
  tcase_add_test(tc, s21_is_less_test4);
  tcase_add_test(tc, s21_is_less_test5);
  tcase_add_test(tc, s21_is_less_test6);
  tcase_add_test(tc, s21_is_less_test7);
  tcase_add_test(tc, s21_is_less_test8);
  tcase_add_test(tc, s21_is_less_test9);
  tcase_add_test(tc, s21_is_less_test10);
  tcase_add_test(tc, s21_is_less_test11);

  suite_add_tcase(s, tc);
  return s;
}
