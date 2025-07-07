#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "single_cache.h"

single_cache_t *init_single_cache_from_file(char *config_path)
{
  int b, E, s, ret;
  FILE *config_fp;

  config_fp = fopen(config_path, "rt");
  if (config_fp == NULL)
  {
    printf("Failed to open configuration file %s\n", config_path);
    return NULL;
  }

  ret = fscanf(config_fp, "%d %d %d", &b, &E, &s);
  if (ret != 3)
  {
    printf("Invalid configuration format\n");
    return NULL;
  }
  fclose(config_fp);

  if (b <= 0 || E <= 0 || s <= 0 || b > 16 || s > 16)
  {
    printf("Invalid configuration parameter: b=%d, E=%d, s=%d\n", b, E, s);
    return NULL;
  }

  return init_single_cache_with_param(b, E, s);
}

single_cache_t *init_single_cache_with_param(int b, int E, int s)
{
  single_cache_t *cache = malloc(sizeof(single_cache_t));
  cache->b = b;
  cache->B = 1 << b;
  cache->E = E;
  cache->s = s;
  cache->S = 1 << s;

  int num_sets = cache->S;
  int num_line = cache->E;
  cache->sets = malloc(num_sets * sizeof(cache_set_t));
  for (int i = 0; i < num_sets; i++)
  {
    cache->sets[i] = malloc(num_line * sizeof(cache_line_t));
    for (int j = 0; j < num_line; j++)
    {
      cache->sets[i][j].valid_flag = 0;
      cache->sets[i][j].tag = 0;
      cache->sets[i][j].age = 0;
    }
  }

  return cache;
}

int access_with_single_cache(single_cache_t *cache, addr_t addr)
{
  int num_sets = cache->S;
  int num_lines = cache->E;
  int block_bits = cache->b;
  int set_bits = cache->s;
  int tag_bits = ADDRESS_LENGTH - block_bits - set_bits;

  addr_t block_mask = (1 << block_bits) - 1;
  addr_t set_mask = (1 << set_bits) - 1;
  addr_t tag_mask = (1 << tag_bits) - 1;

  addr_t block_offset = addr & block_mask;
  addr_t set_index = (addr >> block_bits) & set_mask;
  addr_t tag = (addr >> (block_bits + set_bits)) & tag_mask;

  cache_set_t target_set = cache->sets[set_index];
  for (int i = 0; i < num_lines; i++)
  {
    if (target_set[i].valid_flag && (target_set[i].tag == tag))
    {
      // HIT!!
      for (int j = 0; j < num_lines; j++)
      {
        if (target_set[j].valid_flag)
          target_set[j].age++;
      }
      target_set[i].age = 0;
      return 0;
    }
  }

  // MISS !!
  for (int i = 0; i < num_lines; i++)
  {
    if (!target_set[i].valid_flag)
    {
      target_set[i].valid_flag = 1;
      target_set[i].tag = tag;
      for (int j = 0; j < num_lines; j++)
      {
        if (target_set[j].valid_flag)
          target_set[j].age++;
      }
      target_set[i].age = 0;
      return -1;
    }
  }

  // No 자리
  int insert_index = -1;
  int max_age = -1;
  for (int i = 0; i < num_lines; i++)
  {
    if (target_set[i].age > max_age) {
      max_age = target_set[i].age;
      insert_index = i;
    }
  }
  target_set[insert_index].tag = tag;
  target_set[insert_index].valid_flag = 1;
  for (int i = 0; i < num_lines; i++)
  {
    if (target_set[i].valid_flag)
      target_set[i].age++;
  }
  target_set[insert_index].age = 0;
  return -1;
}
