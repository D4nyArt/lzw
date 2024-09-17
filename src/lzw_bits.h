#ifndef LZW_BITS_H
#define LZW_BITS_H

#include <stdio.h>

enum lzw_bit_resource_type {
  BIT_FILE,
  BIT_BUFFER
};

struct lzw_bit_writer {
  enum lzw_bit_resource_type type;
  unsigned long bits;
  unsigned char pos;
  struct darray *buf;
};

void lzw_bw_init(struct lzw_bit_writer *b,
                 enum lzw_bit_resource_type type,
                 void *dst);
void lzw_bw_pack(struct lzw_bit_writer *b,
                 unsigned char n_bits,
                 unsigned int bits);
struct darray *lzw_bw_result(struct lzw_bit_writer *b);

#endif
