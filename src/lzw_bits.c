#include "lzw_bits.h"
#include "darray.h"
#include <stdlib.h>

static unsigned long gen_mask(unsigned int len) {
  unsigned long mask;

  switch (len) {
    case 0: mask = 0x0000; break;

    case 1: mask = 0x0001; break;
    case 2: mask = 0x0003; break;
    case 3: mask = 0x0007; break;
    case 4: mask = 0x000f; break;

    case 5: mask = 0x001f; break;
    case 6: mask = 0x003f; break;
    case 7: mask = 0x007f; break;
    case 8: mask = 0x00ff; break;

    case 9:  mask = 0x01ff; break;
    case 10: mask = 0x03ff; break;
    case 11: mask = 0x07ff; break;
    case 12: mask = 0x0fff; break;

    case 13: mask = 0x1fff; break;
    case 14: mask = 0x3fff; break;
    case 15: mask = 0x7fff; break;
    case 16: mask = 0xffff; break;

    case 17: mask = 0x0001ffff; break;
    case 18: mask = 0x0003ffff; break;
    case 19: mask = 0x0007ffff; break;
    case 20: mask = 0x000fffff; break;

    case 21: mask = 0x001fffff; break;
    case 22: mask = 0x003fffff; break;
    case 23: mask = 0x007fffff; break;
    case 24: mask = 0x00ffffff; break;

    case 25: mask = 0x01ffffff; break;
    case 26: mask = 0x03ffffff; break;
    case 27: mask = 0x07ffffff; break;
    case 28: mask = 0x0fffffff; break;

    case 29: mask = 0x1fffffff; break;
    case 30: mask = 0x3fffffff; break;
    case 31: mask = 0x7fffffff; break;
    case 32: mask = 0xffffffff; break;

    default: mask = 0x0000; break;
  }
  return mask;
}

/* **************************************** */
/* Public */
/* **************************************** */

void lzw_bw_init(struct lzw_bit_writer *b,
                 enum lzw_bit_resource_type type,
                 void *dst) {
  if (!b) return;
  b->type = type;
  b->bits = 0;
  b->pos = 0;
  b->buf = danew(1024);
}

void lzw_bw_pack(struct lzw_bit_writer *b,
                 unsigned char n_bits,
                 unsigned int bits) {
  unsigned long mask;

  if (!b) return;
  mask = gen_mask(n_bits);
  mask <<= b->pos;
  b->bits |= (bits << b->pos) & mask;
  b->pos += n_bits;
  while (b->pos >= 8) {
    dapush(b->buf, b->bits & 0xff);
    b->pos -= 8;
    b->bits = (b->bits >> 8) & gen_mask(b->pos);
  }
}

struct darray *lzw_bw_result(struct lzw_bit_writer *b) {
  if (!b) return NULL;
  if (b->pos) {
    dapush(b->buf, (unsigned char) (b->bits & gen_mask(b->pos)));
  }
  return b->buf;
}


