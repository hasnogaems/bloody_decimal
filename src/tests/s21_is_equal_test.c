#include "test.h"

// https://colab.research.google.com/drive/1lwKR8vnKY7MZZqmwzlAPxgWJISVUdwau?usp=sharing

START_TEST(s21_equal_test) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test2) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test3) {
  s21_decimal val1 = {{4294967290, 4294967295, 4294967295,
                       0x00000000}};  // sign bit= 0 exponent= 0
  // 79228162514264337593543950330
  s21_decimal val2 = {{1, 0, 0, 0x00070000}};  // sign bit= 0 exponent= -7
  // 1E-7
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
  // 0
}
END_TEST

START_TEST(s21_equal_test4) {
  s21_decimal val1 = {{1, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 1
  s21_decimal val2 = {{1, 0, 0, 0x00070000}};  // sign bit= 0 exponent= -7
  // 1E-7
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test5) {
  s21_decimal val1 = {
      {3270290481, 1272579, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 5465688456866865
  s21_decimal val2 = {
      {3270290481, 1272579, 0, 0x00100000}};  // sign bit= 0 exponent= -16
  // 0.5465688456866865
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test6) {
  s21_decimal val1 = {
      {3270290481, 1272579, 0, 0x000B0000}};  // sign bit= 0 exponent= -11
  // 54656.88456866865
  s21_decimal val2 = {
      {3270290481, 1272579, 0, 0x00100000}};  // sign bit= 0 exponent= -16
  // 0.5465688456866865
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test7) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};

  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test8) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test9) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(0, s21_is_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test10) {
  s21_decimal val1 = {{0, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 0
  s21_decimal val2 = {{0, 0, 0, 0x80000000}};  // sign bit= 1 exponent= 0
  // -0
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
}
END_TEST

Suite *s21_is_equal_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("\033[34m \033[46m IS EQUAL TESTS \033[0m");
  tc = tcase_create("s21_is_equal");

  tcase_add_test(tc, s21_equal_test);
  tcase_add_test(tc, s21_equal_test2);
  tcase_add_test(tc, s21_equal_test3);
  tcase_add_test(tc, s21_equal_test4);
  tcase_add_test(tc, s21_equal_test5);
  tcase_add_test(tc, s21_equal_test6);
  tcase_add_test(tc, s21_equal_test7);
  tcase_add_test(tc, s21_equal_test8);
  tcase_add_test(tc, s21_equal_test9);
  tcase_add_test(tc, s21_equal_test10);

  suite_add_tcase(s, tc);
  return s;
}
