#include "s21_decimal.h"

// bool _get_bit_int(unsigned int num, int pos) { return (num >> pos) & 1; }

int _get_bit_int(unsigned int value, int bit_number) {
  return value & (1 << bit_number);
}

// сдвиг вправо для альтернативного децимала

s21_big_decimal mantissadecimalToBig(s21_decimal value) {
  s21_big_decimal result;
  initializeByBigZeros(&result);
  for (int i = 0; i < 3; i++) {
    result.bits[i] = value.bits[i];
  }
  return result;
}

void set_bit_int(unsigned int* value, int bit_number, int set_value) {
  if (set_value) {
    *value |= (1 << bit_number);
  } else {
    *value = *value & ~(1 << bit_number);
  }
}

void add_one(s21_decimal* value) {
  s21_decimal one = {{1}};

  s21_sum(value, one);
}

void initializeByBigZeros(s21_big_decimal* value) {
  (*value).bits[0] = 0;
  (*value).bits[1] = 0;
  (*value).bits[2] = 0;
  (*value).bits[3] = 0;
  (*value).bits[4] = 0;
  (*value).bits[5] = 0;
}

bool get_bit_value(s21_decimal target, int bit_number) {
  int index = 0;
  while (bit_number >= 32) {
    index++;
    bit_number -= 32;
  }

  bool x = 1 << bit_number & target.bits[index];
  return x;
}

/**
 * сдвиг влево для альтернативного децимала
 * нужно при умножении
 */

int myshiftleft(s21_big_decimal* d, int value) {
  int error = 0;
  if (value != 0) {
    unsigned int overflow = 0;
    unsigned int memory = 0;
    for (int i = 0; i <= 5; i++) {
      memory = d->bits[i];
      d->bits[i] <<= value;
      d->bits[i] |= overflow;
      overflow = memory >> (32 - value);
    }
    if (overflow > 0) error = 1;
  }
  return error;
}

void nullify(s21_decimal* d) {
  d->bits[0] = 0u;
  d->bits[1] = 0u;
  d->bits[2] = 0u;
  d->bits[3] = 0u;
}

void nullifyb(s21_big_decimal* d) {
  d->bits[0] = 0u;
  d->bits[1] = 0u;
  d->bits[2] = 0u;
  d->bits[3] = 0u;
  d->bits[4] = 0u;
  d->bits[5] = 0u;
}

int extractBitSign(s21_decimal number) {
  int result = (number.bits[3] & (1u << 31)) != 0;
  return result;
}

int rem_div_by_ten(s21_decimal value) {
  int order = 0, rem = 0;
  unsigned long buf = 0;

  for (int i = 0; i < 3; i++)  // определяем с какими битами работать
    if (value.bits[i]) order = i;

  buf = value.bits[order];
  while (order >= 0) {
    rem = buf % 10;
    buf = rem * (MAX_UINT + 1) + value.bits[order - 1];
    order--;
  }
  return rem;
}

int mybig_to_decimal(s21_big_decimal big, s21_decimal* decimal, int scale,
                     unsigned int sign) {
  nullify(decimal);
  int error = 0;
  if ((check_345_b(big) > 0 && scale > 0) || scale > 28) {
    int mod = div_by_tenb(&big);
    scale--;
    _bank_rounding(&big, decimal, mod, &scale, sign);
  }
  while (scale < 0) {
    mymulby10(&big);
    scale++;
  }
  int wtf = check_345_b(big);
  if (wtf > 0) {
    error = (sign == 1) ? 2 : 1;
    return error;
  }
  for (int i = 0; i < 3; i++) {
    decimal->bits[i] = big.bits[i];
  }
  decimal->bits[3] |= scale << 16;
  setSign(decimal, sign);
  return error;
}

int check_345_b(s21_big_decimal big) {
  int result = 0;
  if (big.bits[3] > 0 || big.bits[4] > 0 || big.bits[5] > 0) {
    result = 1;
  }
  return result;
}

int tsuboika_is_greater(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  s21_big_decimal big1, big2;
  nullifyb(&big1);
  nullifyb(&big2);
  if (!s21_decimal_is_zero(dec1) && !s21_decimal_is_zero(dec2)) {
    if (retrieveBit(dec1, 127) < retrieveBit(dec2, 127)) {
      res = 1;
    } else if (retrieveBit(dec1, 127) > retrieveBit(dec2, 127)) {
      res = 0;
    } else {
      normalize(dec1, dec2, &big1, &big2);
      for (int i = 191; i >= 0; --i) {
        if (getBigBit(big1, i) > getBigBit(big2, i)) {
          res = 1;

          break;
        } else if (getBigBit(big1, i) < getBigBit(big2, i)) {
          res = 0;

          break;
        }
      }
    }
  }
  if (!s21_decimal_is_zero(dec1) && s21_decimal_is_zero(dec2)) {
    res = 1;
  }
  return res;
}

int tsuboika_is_equal(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  s21_big_decimal big1, big2;
  nullifyb(&big1);
  nullifyb(&big2);
  normalize(dec1, dec2, &big1, &big2);
  if (big1.bits[0] == big2.bits[0] && big1.bits[1] == big2.bits[1] &&
      big1.bits[2] == big2.bits[2] && big1.bits[3] == big2.bits[3] &&
      big1.bits[4] == big2.bits[4] && big1.bits[5] == big2.bits[5]) {
    res = 1;
  }
  return res;
}

int retrieveBit(s21_decimal number, int bit) {
  return (number.bits[bit / 32] & (1u << (bit % 32))) != 0;
}

int getBigBit(s21_big_decimal value, int index) {
  int bits_index = index / 32;
  int int_index = 31 - index % 32;
  int bit = -1;
  if (index > -1 && index < 192) {
    value.bits[bits_index] = value.bits[bits_index] << int_index;
    value.bits[bits_index] = value.bits[bits_index] >> 31;
    bit = value.bits[bits_index] == 0 ? 0 : 1;
  }
  return bit;
}

void my_decimal_to_big(s21_decimal val1, s21_big_decimal* tar1) {
  tar1->bits[0] = val1.bits[0];
  tar1->bits[1] = val1.bits[1];
  tar1->bits[2] = val1.bits[2];
}