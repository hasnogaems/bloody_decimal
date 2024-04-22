#include "s21_decimal.h"

int s21_div(s21_decimal divident_src, s21_decimal divisor,
            s21_decimal *result) {
  int error = 0;
  int scale1 = GETSCALE(divident_src);
  int scale2 = GETSCALE(divisor);
  if (result) {  // if result not null
    if (!(divisor.bits[0] == 0 && divisor.bits[1] == 0 &&
          divisor.bits[2] == 0)) {
      int sign1 = extractBitSign(divident_src);
      int sign2 = extractBitSign(divisor);
      unsigned int sign = 0;
      if (sign1 == sign2) {
        sign = 0;
      } else {
        sign = 1;
      }
      s21_big_decimal divident = {{0}}, divident_srcb = {{0}}, divisorb = {{0}},
                      ostatok = {{0}}, resultb = {{0}}, fraction = {{0}};

      nullify(result);
      int scale = scale1 - scale2;
      // int scale=normalize(divident_src, divisor, &divident_srcb, &divisorb);
      my_decimal_to_big(divident_src, &divident_srcb);
      my_decimal_to_big(divisor, &divisorb);
      int zero = 1;
      // int divident=0;
      // int divisor=0;
      int i = 191;
      while (s21_is_lessb(divident_srcb, divisorb) && scale < 28) {
        mymulby10(&divident_srcb);
        scale++;
      }
      for (; i >= 0 && zero; i--)
        if (getBigBit(divident_srcb, i)) {  // срезаем нули
          zero = 0;
          s21_set_bitb(&divident, 0, getBigBit(divident_srcb, i));
        }  // ставим 1 в делимое
      i++;
      for (; (i) >= 0;) {
        int position = 0;
        while (s21_is_lessb(divident, divisorb) && i >= 0) {
          myshiftleft(&resultb, 1);
          s21_set_bitb(&resultb, 0, 0);  // ставим ноль пока не отнимается
          i--;
          ostatok = divident;
          position++;
          if (i >= 0) error = grow_dividentb(&divident, divident_srcb, i);

        }  // now divident can be actually substracted from
        if (i >= 0) {
          while (s21_is_greater_or_equalb(divident, divisorb)) {
            mysubb(divident, divisorb, &ostatok);

            myshiftleft(&resultb, 1);
            s21_set_bitb(&resultb, 0, 1);

            divident = ostatok;
          }
          i--;
          grow_dividentb(&divident, divident_srcb, i);
        }
      }
      while (!zeroBigDecimal(ostatok) && scale <= 28) {
        // ставим ноль пока не отнимается
        mymulby10(&ostatok);
        mymulby10(&resultb);
        scale++;
        fraction = big_division(&ostatok, divisorb);
        // myaddb(ostatok, fraction, &fraction);

        myaddb(resultb, fraction, &resultb);
      }

      error = mybig_to_decimal(resultb, result, scale, sign);

    } else {
      error = 3;
    }
  } else {
    error = 1;
  }

  return error;
}

int grow_dividentb(s21_big_decimal *divident, s21_big_decimal divident_src,
                   int i) {
  int error = 0;
  error = myshiftleft(divident, 1);
  s21_set_bitb(divident, 0, getBigBit(divident_src, i));
  return error;
}

s21_big_decimal big_division(s21_big_decimal *value_1,
                             s21_big_decimal value_2) {
  s21_big_decimal res = {{0, 0, 0, 0, 0, 0}};
  s21_big_decimal shifted_bit = {{1, 0, 0, 0, 0, 0}};
  while (big_comparison(*value_1, value_2) == VAL1_GREATER_THAN_VAL2) { //если делимое больше делителя
    s21_big_decimal del = value_2; //пишем в делитель делитель
    int i = 0;
    if (big_comparison(del, *value_1) == VAL2_GREATER_THAN_VAL1 || //если делитель больше делимого
        big_comparison(del, *value_1) == VALUES_IS_EQUAL) { //или если делитель равен делимому
      while (big_comparison(del, *value_1) == VAL2_GREATER_THAN_VAL1 ||//пока тоже самое
             big_comparison(del, *value_1) == VALUES_IS_EQUAL) {
        del = big_shift_bits(del, -1); //сдвигаем делитель влево на 1, как это поможет сделать делимое больше, мы же хотим делимое больше
        ++i;
      }
      del = big_shift_bits(del, 1); // и вправо на 1 и i вниз? Почему?
      i--;
    }
    //В результ мы добавляем 1 со сдвигом влево на i
    myaddb(res, big_shift_bits(shifted_bit, -i), &res);
    if (big_comparison(*value_1, del) == VAL1_GREATER_THAN_VAL2 ||
        big_comparison(*value_1, del) == VALUES_IS_EQUAL) {
      mysubb(*value_1, del, value_1);
    }
    del = big_shift_bits(del, -1);
  }
  return res;
}

int big_comparison(s21_big_decimal value_1, s21_big_decimal value_2) {
  int bit_value_1 = 0;
  int bit_value_2 = 0;
  int res = 0;
  for (int i = 191; i > -1; i--) {
    bit_value_1 = get_bit_valueb(value_1, i);
    bit_value_2 = get_bit_valueb(value_2, i);

    if (bit_value_1 < bit_value_2) {
      res = 2;
      break;
    } else if (bit_value_1 > bit_value_2) {
      res = 1;
      break;
    } else if (i == 0 && bit_value_1 == bit_value_2) {
      res = 0;
    }
  }
  return res;
}

s21_big_decimal big_shift_bits(s21_big_decimal dec, int shif) {
  s21_big_decimal answer = {{0, 0, 0, 0, 0, 0}};

  if (shif > 0) {
    for (int i = 0; i < 192 - shif; i++) {
      if (get_bit_valueb(dec, i + shif)) {
        s21_set_bitb(&answer, i, 1);
      }
    }
  } else {
    for (int i = 191; i > -1 + (shif * -1); i--) {
      if (get_bit_valueb(dec, i + shif)) {
        s21_set_bitb(&answer, i, 1);
      }
    }
  }

  return answer;
}
