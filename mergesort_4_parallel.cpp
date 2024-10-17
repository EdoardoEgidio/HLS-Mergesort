#include "mergesort.hpp"

#define PRAMGA_SUB(x) _Pragma(#x)
#define PRAGMA_HLS(x) PRAMGA_SUB(x)

#define unroll_factor 4
#define partition_factor 4

void mergesort(data_t in[SIZE], data_t out[SIZE]) {
PRAGMA_HLS(HLS array_partition variable=in type=block factor=partition_factor)
PRAGMA_HLS(HLS array_partition variable=out type=block factor=partition_factor)
window:
  for (len_t w = 2; w <= SIZE; w *= 2) {
PRAGMA_HLS(HLS unroll factor=unroll_factor)
offset:
    for (len_t os = 0; os < SIZE / w; os++) {
      len_t start = w * os;
      len_t end = w * os + w - 1;
      len_t mid = ((2 * w * os) + w - 1) / 2;
      const len_t left_size = mid - start + 1;
      const len_t right_size = end - mid;
      len_t left_count = 0;
      len_t right_count = 0;
      len_t out_count = start;
merge:
      for (; left_count < left_size && right_count < right_size; out_count++) {
PRAGMA_HLS(HLS unroll factor=unroll_factor)
        data_t left_el = in[start + left_count];
        data_t right_el = in[mid + right_count + 1];
        if (left_el <= right_el) {
          out[out_count] = left_el;
          left_count++;
        } else {
          out[out_count] = right_el;
          right_count++;
        }
      }
copy_left:
      for (; left_count < left_size; left_count++) {
PRAGMA_HLS(HLS unroll factor=unroll_factor)
        out[out_count] = in[start + left_count];
        out_count++;
      }
copy_right:
      for (; right_count < right_size; right_count++) {
PRAGMA_HLS(HLS unroll factor=unroll_factor)
        out[out_count] = in[mid + right_count + 1];
        out_count++;
      }
    }
copy_back:
    for (len_t i = 0; i < SIZE; i++) {
PRAGMA_HLS(HLS unroll factor=unroll_factor)
      in[i] = out[i];
    }
  }
copy_out:
  for(len_t i = 0; i < SIZE; i++){
PRAGMA_HLS(HLS unroll factor=unroll_factor)
      out[i] = in[i];
    }
}