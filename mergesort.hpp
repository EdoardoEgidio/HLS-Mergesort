#ifndef _MERGE_SORT_
#define _MERGE_SORT_

#include <cstdint>
#include <stdint.h>

#define SIZE 1024

typedef int32_t data_t;
typedef uint16_t len_t;

void mergesort(data_t in[SIZE], data_t out[SIZE]);

#endif //_MERGE_SORT_
