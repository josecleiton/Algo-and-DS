#include <iostream>
#include "sort.hpp"
#include "search.hpp"
#define MAX 100000
using namespace std;

void testSearch(void){
    int v[] = {1,2,10,14,50,99,100};
    searching<int> searchClass;
    searchClass.compare(&searching<int>::binary, &searching<int>::linear, vector<int>(v, v+sizeof(v)/sizeof(*v)), 101);
}

void testSort(void){
    int b[MAX];
    for(int i=0; i<MAX; i++)
        b[i] = rand();
    sorting<int> sortClass;
    sortClass.compare(&sorting<int>::quickSort, &sorting<int>::radixSort, vector<int>(b, b+MAX));
    //auto result = sortClass.insertionSort(vector<int>(b, b+MAX));
    //cout << is_sorted(result.begin(), result.end()) << endl;
    //sortClass.printArray();
}

int main(void){
    testSort();
    return 0;
}