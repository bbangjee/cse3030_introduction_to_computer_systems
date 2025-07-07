#ifndef CACHE_TYPES_H
#define CACHE_TYPES_H

#define ADDRESS_LENGTH 64

// Type for memory address.
typedef unsigned long long addr_t;

// Type for cache line.
typedef struct cache_line_t {
  int valid_flag;
  addr_t tag;
  int age;
} cache_line_t;

// Cache set is a pointer to an array of cache lines.
typedef cache_line_t* cache_set_t;

#endif /* CACHE_TYPES_H */
