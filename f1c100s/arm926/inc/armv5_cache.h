#ifndef ARMV5_CACHE_H
#define ARMV5_CACHE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

static inline void cache_inv_range(unsigned long start, unsigned long end) {
    extern void v5_cache_inv_range(unsigned long start, unsigned long end);
    v5_cache_inv_range(start, end);
}

static inline void cache_clean_range(unsigned long start, unsigned long end) {
    extern void v5_cache_clean_range(unsigned long start, unsigned long end);
    v5_cache_clean_range(start, end);
}

static inline void cache_flush_range(unsigned long start, unsigned long end) {
    extern void v5_cache_flush_range(unsigned long start, unsigned long end);
    v5_cache_flush_range(start, end);
}

#ifdef __cplusplus
}
#endif

#endif // ARMV5_CACHE_H
