#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <vector>
#include <iostream>
#include "vec3.h" /// projeto em https://github.com/C4io-z/vec3 

class quicksort{
    public:
        quicksort();
        virtual~quicksort();
        std::vector<vec3> elements;
        std::vector<int> indices;
        void startIndex();
        void setIndex();
        int partition (const int start, const int end);
        void swap(const int i, const int j);
        void Quicksort(const int start, const int end);
        void Quicksort();
        void print();
};
#endif
