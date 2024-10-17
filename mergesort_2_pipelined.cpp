#include "mergesort.hpp"
#include <assert.h>

void merge(data_t in[SIZE], data_t out[SIZE], len_t start, len_t mid, len_t end){
    len_t f1 = start;
    len_t f2 = mid;
    for(len_t i = start; i < end; i++){
#pragma HLS PIPELINE II=1
        data_t tmp1 = in[f1];
        data_t tmp2 = in[f2];
        if(f2 == end || (f1 < mid && tmp1 <= tmp2)){
            out[i] = tmp1;
            f1++;
        }else{
            assert(f2 < end);
            out[i] = tmp2;
            f2++;
        }
    }
}

void mergesort(data_t in[SIZE], data_t out[SIZE]){
    data_t tmp[SIZE] = {0};
    window_growth: 
    for(len_t window = 1; window < SIZE; window *= 2){
        merge_subarrays:
        for(len_t s = 0; s < SIZE; s += 2*window){
            len_t m = ((s + window) >= SIZE) ? SIZE : (s + window);
            len_t e = ((s + 2*window) >= SIZE) ? SIZE : (s + 2*window);
            merge(input, tmp, s, m, e);
        }
        copy:
        for(len_t i = 0; i < SIZE; i++)
#pragma HLS PIPELINE II=1
            input[i] = tmp[i];
    }
    copy_out:
    for(len_t i = 0; i < SIZE; i++)
#pragma HLS PIPELINE II=1
        output[i] = input[i];
}
