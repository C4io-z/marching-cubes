#include "qucksort.h"


quicksort::quicksort(){

}

quicksort::~quicksort(){

}
void quicksort::startIndex(){
    for(unsigned int i = 0; i < indices.size(); i++){
            elements[indices[i]].w = i;
    }
}
void quicksort::setIndex(){
    std::vector<vec3> vertex;
    int temp = -1;
    for(unsigned int i = 0; i < elements.size(); i++){
        if(elements[i].s){
            vertex.push_back(elements[i]);
            temp++;
            indices[elements[i].w] = temp;
            for(unsigned int j = i+1; elements[i].ID() == elements[j].ID() && j < elements.size(); j++){
                indices[elements[j].w] = temp;
                elements[j].s = false;
            }//*/
        }
    }
    elements = vertex;
}
int quicksort::partition(const int start, const int end){
    int i = start;
    for(int j = start; j < end; j++){
        if(elements[j].ID() <= elements[end].ID()){
            swap(i++, j);
        }
    }
    swap(i, end);
    return i;
}
void quicksort::swap(const int i, const int j){
    vec3 k = elements[i];
    elements[i] = elements[j];
    elements[j] = k;
}
void quicksort::Quicksort(const int start, const int end){
    if (start >= end) return;
    int pivot = partition(start, end);
    Quicksort(start, pivot - 1);
    Quicksort(pivot + 1, end);
}
void quicksort::Quicksort(){
    Quicksort(0, elements.size()-1);
}
void quicksort::print(){
    for(unsigned int i = 0; i < elements.size(); i++){
        std::cout<< elements[i].x << " : " << elements[i].y << " : " << elements[i].z << std::endl;
    }
}
