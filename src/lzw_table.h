#ifndef LZW_TABLE_H
#define LZW_TABLE_H

#include "darray.h"
#include <stddef.h>

#define LZW_MAX_ENTRY_EXP 12
#define LZW_MAX_ENTRIES (1 << LZW_MAX_ENTRY_EXP)

enum lzw_table_type {
  LZW_TABLE_COMPRESS,
  LZW_TABLE_DECOMPRESS
};

struct lzw_entry {
  unsigned int len;
  unsigned int prev;
  unsigned int code;
  unsigned char val;
};

struct lzw_table {
  enum lzw_table_type type;
  unsigned int n_entries;
  size_t size;
  char *initialized;
  struct lzw_entry *entries;
};

void lzw_table_init(struct lzw_table *t,
                    enum lzw_table_type type,
                    unsigned char bit_size);
void lzw_table_deinit(struct lzw_table *t);
void lzw_table_add(struct lzw_table *t, struct lzw_entry *e);
int lzw_table_lookup_entry(struct lzw_table *t,
                           struct lzw_entry *e,
                           unsigned int *out_code);
#endif
