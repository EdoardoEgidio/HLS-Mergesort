#include "mergesort.hpp"
#include <assert.h>

void mergesort(data_t in[SIZE], data_t out[SIZE]){
    data_t tmp[SIZE] = {0};
    window_growth: 
    for(len_t window = 1; window < SIZE; window *= 2){
        len_t f1 = 0;
        len_t f2 = window;
        len_t mid = (window > SIZE) ? SIZE : window;
        len_t end = (2*window > SIZE) ? SIZE : 2*window;
        merge_subarrays:
        for(len_t i = 0; i < SIZE; i++){
#pragma HLS PIPELINE II=1
            data_t tmp1 = in[f1];
            data_t tmp2 = (f2 == end) ? 0 : in[f2];
            if(f2 == end || (f1 < mid && tmp1 <= tmp2)){
                tmp[i] = tmp1;
                f1++;
            }else{
                assert(f2 < end);
                tmp[i] = tmp2;
                f2++;
            }
            if(f1 == mid && f2 == end){
                f1 = end;
                mid = ((mid + 2*window) >= SIZE) ? SIZE : (mid + 2*window);
                end = ((end + 2*window) >= SIZE) ? SIZE : (end + 2*window);
                f2 = mid;
            }
        }
        copy:
        for(len_t i = 0; i < SIZE; i++){
#pragma HLS PIPELINE II=1
            in[i] = tmp[i];
        }
    }        
    copy_out:
    for(len_t i = 0; i < SIZE; i++){
#pragma HLS PIPELINE II=1
        out[i] = in[i];
    }
}