#ifndef SINGLE_CACHE_H
#define SINGLE_CACHE_H

#include "types.h"

// Type for single-level cache memory.
typedef struct _single_cache_t {
  int b; // Number of block offset bits.
  int B; // Size of cache block.
  int E; // Number of cache lines per set.
  int s; // Number of set index bits.
  int S; // Number of sets in the cache memory.
  cache_set_t* sets; // Pointer to an array of cache sets.
} single_cache_t;

// Allocate and initialize a 'single_cache_t' structure based on the provided
// cache configuration file. Return a pointer to the initalized structure.
single_cache_t* init_single_cache_from_file(char *config_path);

// Allocate and initialize a 'single_cache_t' structure with the provided cache
// parameters. Return a pointer to the initalized structure.
single_cache_t* init_single_cache_with_param(int b, int E, int s);

// Simulate memory access on address 'addr'. Return 0 if the access results in a
// cache hit and return -1 if it raises a cache miss. The content of 'cache'
// must be updated accordingly.
int access_with_single_cache(single_cache_t* cache, addr_t addr);

#endif /* SINGLE_CACHE_H */
