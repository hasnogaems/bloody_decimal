#include "s21_decimal.h"

int s21_is_greater(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  if (!s21_decimal_is_zero(dec1) && !s21_decimal_is_zero(dec2)) {
    if (get_bit(dec1, 127) < get_bit(dec2, 127)) {
      res = 1;
    } else if (get_bit(dec1, 127) > get_bit(dec2, 127)) {
      res = 0;
    } else {
      normalization(&dec1, &dec2);
      for (int i = 95; i >= 0; --i) {
        if (get_bit(dec1, i) > get_bit(dec2, i)) {
          if (!get_bit(dec1, 127)) {
            res = 1;
          }
          break;
        } else if (get_bit(dec1, i) < get_bit(dec2, i)) {
          if (get_bit(dec1, 127)) {
            res = 1;
          }
          break;
        }
      }
    }
  }
  return res;
}

int s21_is_less(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_equal(dec1, dec2) || s21_is_greater(dec1, dec2) ? 0 : 1);
}

int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_equal(dec1, dec2) || s21_is_less(dec1, dec2) ? 1 : 0);
}

int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_equal(dec1, dec2) || s21_is_greater(dec1, dec2) ? 1 : 0);
}

int s21_is_equal(s21_decimal mem1, s21_decimal mem2) {
  int res = 1;
  s21_big_decimal big1, big2;
  nullifyb(&big1);
  nullifyb(&big2);
  normalize(mem1, mem2, &big1, &big2);

  if (get_sign(mem1) == get_sign(mem2)) {
    for (int i = 191; i >= 0; i--) {
      if (get_bit_valueb(big1, i) != get_bit_valueb(big2, i)) res = 0;
    }
    return res;
  }
  return 0;
}

int s21_is_not_equal(s21_decimal mem1, s21_decimal mem2) {
  int res = 1;
  s21_big_decimal big1, big2;
  nullifyb(&big1);
  nullifyb(&big2);
  normalize(mem1, mem2, &big1, &big2);
  if (get_sign(mem1) == get_sign(mem2)) {
    for (int i = 191; i >= 0; i--) {
      if (get_bit_valueb(big1, i) == get_bit_valueb(big2, i)) res *= 0;
    }
  }
  if (res && (get_scale(mem1) != get_scale(mem2))) res = 0;
  return res;
}

void normalization(s21_decimal *dec_one, s21_decimal *dec_two) {
  int ext_one = get_scale(*dec_one);
  int ext_two = get_scale(*dec_two);
  if (ext_one > 28) {
    while (ext_one != 28) {
      division_by_ten(*dec_one, dec_one);
      set_scale(dec_one, --ext_one);
    }
  }
  if (ext_two > 28) {
    while (ext_two != 28) {
      division_by_ten(*dec_two, dec_two);
      set_scale(dec_two, --ext_two);
    }
  }
  int diff = ext_one - ext_two;
  if (diff > 0)
    equalization(ext_one, ext_two, dec_one, dec_two);
  else if (diff < 0)
    equalization(ext_two, ext_one, dec_two, dec_one);
}

void equalization(int ext_big, int ext_small, s21_decimal *big_ext,
                  s21_decimal *small_ext) {
  int diff = ext_big - ext_small;
  s21_decimal tmp = *small_ext;
  int work_mul = 1;
  while (diff > 0 && work_mul) {
    mymulby10s(&tmp);
    if (get_before_scale(tmp)) work_mul = 0;
    if (work_mul) {
      diff--;
      set_scale(&tmp, ++ext_small);
      *small_ext = tmp;
    }
  }
  while (diff) {
    division_by_ten(*big_ext, big_ext);
    set_scale(big_ext, --ext_big);
    diff--;
  }
}

int get_before_scale(s21_decimal dec) { return (dec.bits[3] & 32767); }