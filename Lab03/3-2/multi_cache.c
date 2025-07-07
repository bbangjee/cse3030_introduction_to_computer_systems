#include <stdio.h>
#include <stdlib.h>
#include "multi_cache.h"

multi_cache_t *init_multi_cache_from_file(char *config_path)
{
  int b, l, ret;
  FILE *config_fp;

  config_fp = fopen(config_path, "rt");
  if (config_fp == NULL)
  {
    printf("Failed to open configuration file %s\n", config_path);
    return NULL;
  }

  ret = fscanf(config_fp, "%d %d", &b, &l);
  if (ret != 2)
  {
    printf("Invalid configuration format\n");
    fclose(config_fp);
    return NULL;
  }

  if (b <= 0 || l <= 0 || b > 16)
  {
    printf("Invalid configuration parameter: b=%d, l=%d\n", b, l);
    fclose(config_fp);
    return NULL;
  }

  multi_cache_t *cache = malloc(sizeof(multi_cache_t));
  if (cache == NULL)
  {
    fclose(config_fp);
    return NULL;
  }

  cache->n = l;
  cache->caches = malloc(l * sizeof(single_cache_t *));
  if (cache->caches == NULL)
  {
    free(cache);
    fclose(config_fp);
    return NULL;
  }

  for (int i = 0; i < l; i++)
  {
    int E, s, tmp;
    tmp = fscanf(config_fp, "%d %d", &E, &s);
    if (tmp != 2)
    {
      printf("Invalid configuration format\n");
      fclose(config_fp);
      for (int j = 0; j < i; j++)
      {
        if (cache->caches[j] != NULL)
        {
          if (cache->caches[j]->sets != NULL)
          {
            int num_sets = cache->caches[j]->S;
            for (int k = 0; k < num_sets; k++)
            {
              free(cache->caches[j]->sets[k]);
            }
            free(cache->caches[j]->sets);
          }
          free(cache->caches[j]);
        }
      }
      free(cache->caches);
      free(cache);
      return NULL;
    }
    if (E <= 0 || s <= 0 || s > 16)
    {
      printf("Invalid configuration parameter: E=%d, s=%d\n", E, s);
      for (int j = 0; j < i; j++)
      {
        if (cache->caches[j] != NULL)
        {
          if (cache->caches[j]->sets != NULL)
          {
            int num_sets = cache->caches[j]->S;
            for (int k = 0; k < num_sets; k++)
            {
              free(cache->caches[j]->sets[k]);
            }
            free(cache->caches[j]->sets);
          }
          free(cache->caches[j]);
        }
      }
      fclose(config_fp);
      free(cache->caches);
      free(cache);
      return NULL;
    }
    cache->caches[i] = init_single_cache_with_param(b, E, s);
    if (cache->caches[i] == NULL)
    {
      fclose(config_fp);
      for (int j = 0; j < i; j++)
      {
        if (cache->caches[j] != NULL)
        {
          if (cache->caches[j]->sets != NULL)
          {
            int num_sets = cache->caches[j]->S;
            for (int k = 0; k < num_sets; k++)
            {
              free(cache->caches[j]->sets[k]);
            }
            free(cache->caches[j]->sets);
          }
          free(cache->caches[j]);
        }
      }
      free(cache->caches);
      free(cache);
      return NULL;
    }
  }
  fclose(config_fp);
  return cache;
}

int access_with_multi_cache(multi_cache_t *cache, addr_t addr)
{
  int n = cache->n;
  for (int i = 0; i < n; i++)
  {
    int res = access_with_single_cache(cache->caches[i], addr);
    if (res == 0)
      return i;
  }
  return -1;
}
