#include "lzw.h"
#include "lzw_bits.h"
#include "lzw_table.h"
#include "darray.h"
#include <stdio.h>
#include <stdlib.h>


void compress(unsigned char bit_size,
              unsigned long size,
              unsigned char *src,
              unsigned long *out_len,
              unsigned char **output,
              int gif_format) {
    unsigned char bit_width = 12;  // Fijo a 12 bits
    struct lzw_bit_writer b;
    struct lzw_table ctable;
    struct darray *result;

    if (!output) return;
    if (!out_len) return;
    lzw_bw_init(&b, BIT_BUFFER, NULL);
    lzw_table_init(&ctable, LZW_TABLE_COMPRESS, bit_size);
    if (gif_format) lzw_bw_pack(&b, bit_width, 1 << bit_size);  // Código de "clear"
    for (;;) {
        unsigned int code = 0;
        struct lzw_entry e = { 0 };

        // Construir la siguiente entrada del diccionario
        do {
            e.val = *src++;
            e.prev = code;
            e.len++;
            size--;
            if (!size) {
                lzw_bw_pack(&b, bit_width, code);
                code = *--src;
                break;
            }
        } while (lzw_table_lookup_entry(&ctable, &e, &code));

        lzw_table_add(&ctable, &e);
        lzw_bw_pack(&b, bit_width, code);
        if (!size) break;
        size++;
        src--;
    }

    if (gif_format) lzw_bw_pack(&b, bit_width, (1 << bit_size) + 1);  // Código de "fin de stream"
    lzw_table_deinit(&ctable);
    result = lzw_bw_result(&b);
    *out_len = dalen(result);
    *output = dapeel(result);
}

/* **************************************** */
/* Public */
/* **************************************** */

void lzw_compress(unsigned char bit_size,
                  unsigned long size,
                  unsigned char *src,
                  unsigned long *out_len,
                  unsigned char **result) {
  compress(bit_size, size, src, out_len, result, 0);
}

void lzw_compress_gif(unsigned char bit_size,
                      unsigned long size,
                      unsigned char *src,
                      unsigned long *out_len,
                      unsigned char **result) {
  compress(bit_size, size, src, out_len, result, 1);
}


