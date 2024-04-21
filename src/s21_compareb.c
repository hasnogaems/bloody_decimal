#include "s21_decimal.h"
int s21_is_greaterb(s21_big_decimal mem1,
                    s21_big_decimal mem2) {  // ИСПРАВИТЬ В ЧЕТВЕРГ
  int res = 0;

  for (int i = 191; i >= 0; i--) {
    if (get_bit_valueb(mem1, i) != get_bit_valueb(mem2, i)) {
      if (get_bit_valueb(mem1, i)) res = 1;
      break;
    }
  }
  return res;
}

int s21_is_lessb(s21_big_decimal dec1, s21_big_decimal dec2) {
  return ((s21_is_equalb(dec1, dec2) || s21_is_greaterb(dec1, dec2)) ? 0 : 1);
}

int s21_is_less_or_equalb(s21_big_decimal dec1, s21_big_decimal dec2) {
  return (s21_is_equalb(dec1, dec2) || s21_is_lessb(dec1, dec2) ? 1 : 0);
}

int s21_is_greater_or_equalb(s21_big_decimal dec1, s21_big_decimal dec2) {
  return (s21_is_equalb(dec1, dec2) || s21_is_greaterb(dec1, dec2) ? 1 : 0);
}

int s21_is_equalb(s21_big_decimal mem1, s21_big_decimal mem2) {
  int res = 1;

  for (int i = 191; i >= 0; i--) {
    if (get_bit_valueb(mem1, i) != get_bit_valueb(mem2, i)) res = 0;
  }
  return res;
}

int zeroBigDecimal(s21_big_decimal v) {
  int arg = 0;
  if (!v.bits[0] && !v.bits[1] && !v.bits[2] && !v.bits[3] && !v.bits[4] &&
      !v.bits[5])
    arg = 1;
  return arg;
}