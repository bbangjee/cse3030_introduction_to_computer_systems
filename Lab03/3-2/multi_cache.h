#ifndef MULTI_CACHE_H
#define MULTI_CACHE_H

#include "single_cache.h"

// Type for single-level cache memory.
typedef struct _multi_cache_t {
  // Number of total levels in this cache.
  int n;
  // Pointer to an array of single-level cache. The array has 'n' elements, and
  // each element is a pointer to 'single_cache_t' structure.
  single_cache_t **caches;
} multi_cache_t;

// Allocate and initialize a 'multi_cache_t' structure based on the provided
// cache configuration file. Return a pointer to the initalized structure.
multi_cache_t* init_multi_cache_from_file(char *config_path);

// Simulate memory access on address 'addr'. Return -1 if the access eventually
// raised a cache miss (failed to find the data in any of the cache levels).
// Return 'N' if a hit occured in the cache memory at level 'N'. Note that the
// cache memory closest to the CPU is level 0 (L0 cache).
int access_with_multi_cache(multi_cache_t* cache, addr_t addr);

#endif /* MULTI_CACHE_H */
