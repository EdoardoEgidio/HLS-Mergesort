#include "mergesort.hpp"
#include <cstdint>
#include <iostream>
#include <random>
#include <algorithm>

int main(){
    int errors = 0;
    int seed = 1234578;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<data_t> dist(INT32_MIN, INT32_MAX);

    data_t to_sort[SIZE] = {0};
    data_t sorted[SIZE] = {0};
    data_t golden[SIZE] = {0};

    //1
    //Basic functionality
    for(int i = 0; i < SIZE; i++){
        data_t n = dist(rng);
        to_sort[i] = n;
        golden[i] = n;
    }
    std::sort(golden, golden+SIZE);

    mergesort(to_sort, sorted);

    for(int i = 0; i < SIZE; i++){
        //std::cout<<golden[i]<<" | "<<sorted[i]<<std::endl;
        if(golden[i] != sorted[i])
            errors++;
    }
    if(!errors) std::cout<<"Test 1 passed"<<std::endl;

    //2
    //Partially full input
    for(int i = 0; i < SIZE; i++){
        data_t n = dist(rng);
        if(i < SIZE/3){
            to_sort[i] = n;
            golden[i] = n;
        }else{
            to_sort[i] = INT32_MAX;
            golden[i] = INT32_MAX;
        }
    }
    std::sort(golden, golden+SIZE);

    mergesort(to_sort, sorted);

    for(int i = 0; i < SIZE; i++){
        //std::cout<<golden[i]<<" | "<<sorted[i]<<std::endl;
        if(golden[i] != sorted[i])
            errors++;
    }
    if(!errors) std::cout<<"Test 2 passed"<<std::endl;

    //3
    //Repeted elemnts
    data_t n = dist(rng);
    for(int i = 0; i < SIZE; i++){
        if(i < SIZE/3){
            to_sort[i] = n;
            golden[i] = n;
        }else{
            to_sort[i] = n/2;
            golden[i] = n/2;
        }
    }
    std::sort(golden, golden+SIZE);

    mergesort(to_sort, sorted);

    for(int i = 0; i < SIZE; i++){
        //std::cout<<golden[i]<<" | "<<sorted[i]<<std::endl;
        if(golden[i] != sorted[i])
            errors++;
    }
    if(!errors) std::cout<<"Test 3 passed"<<std::endl;

    //4
    for(int r = 0; r < 10; r++){
        for(int i = 0; i < SIZE; i++){
            data_t n = dist(rng);
            to_sort[i] = n;
            golden[i] = n;
        }
        std::sort(golden, golden+SIZE);

        mergesort(to_sort, sorted);

        for(int i = 0; i < SIZE; i++){
            //std::cout<<golden[i]<<" | "<<sorted[i]<<std::endl;
            if(golden[i] != sorted[i])
                errors++;
        }
        if(!errors) std::cout<<"Test "<<4+r<<" passed"<<std::endl;
    }

    return (errors == 0) ? 0:-1;
}