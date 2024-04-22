#include "test.h"

START_TEST(s21_is_less_test) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test2) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test4) {
  s21_decimal val1 = {{1234567, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 1234567
  s21_decimal val2 = {{1234567, 0, 0, 0x00030000}};  // sign bit= 0 exponent= -3
  // 1234.567
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test5) {
  s21_decimal val1 = {{1, 0, 0, 0x00010000}};  // sign bit= 0 exponent= -1
  // 0.1
  s21_decimal val2 = {{10, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 10
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test8) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00010000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test9) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test10) {
  s21_decimal val1 = {{1, 0, 0, 0x80000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};

  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test3) {
  s21_decimal val1 = {{4294967290, 4294967295, 4294967295,
                       0x00000000}};  // sign bit= 0 exponent= 0
  // 79228162514264337593543950330
  s21_decimal val2 = {{1, 0, 0, 0x00070000}};  // sign bit= 0 exponent= -7
  // 1E-7
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
  // 0
}
END_TEST

START_TEST(s21_equal_test4) {
  s21_decimal val1 = {{1, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 1
  s21_decimal val2 = {{1, 0, 0, 0x00070000}};  // sign bit= 0 exponent= -7
  // 1E-7
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test5) {
  s21_decimal val1 = {
      {3270290481, 1272579, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 5465688456866865
  s21_decimal val2 = {
      {3270290481, 1272579, 0, 0x00100000}};  // sign bit= 0 exponent= -16
  // 0.5465688456866865
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test6) {
  s21_decimal val1 = {
      {3270290481, 1272579, 0, 0x000B0000}};  // sign bit= 0 exponent= -11
  // 54656.88456866865
  s21_decimal val2 = {
      {3270290481, 1272579, 0, 0x00100000}};  // sign bit= 0 exponent= -16
  // 0.5465688456866865
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test7) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};

  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test8) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test10) {
  s21_decimal val1 = {{0, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 0
  s21_decimal val2 = {{0, 0, 0, 0x80000000}};  // sign bit= 1 exponent= 0
  // -0
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

Suite *s21_is_less_or_equal_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("\033[34m \033[46m IS LESS OR EQUAL TESTS \033[0m");
  tc = tcase_create("s21_is_less_or_equal");

  tcase_add_test(tc, s21_is_less_test);
  tcase_add_test(tc, s21_is_less_test2);
  tcase_add_test(tc, s21_is_less_test4);
  tcase_add_test(tc, s21_is_less_test5);
  tcase_add_test(tc, s21_is_less_test8);
  tcase_add_test(tc, s21_is_less_test9);
  tcase_add_test(tc, s21_is_less_test10);
  tcase_add_test(tc, s21_equal_test3);
  tcase_add_test(tc, s21_equal_test4);
  tcase_add_test(tc, s21_equal_test5);
  tcase_add_test(tc, s21_equal_test6);
  tcase_add_test(tc, s21_equal_test7);
  tcase_add_test(tc, s21_equal_test8);
  tcase_add_test(tc, s21_equal_test10);

  suite_add_tcase(s, tc);
  return s;
}
