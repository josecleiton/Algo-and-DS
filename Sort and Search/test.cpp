#include <iostream>
#include "sort.hpp"
#include "search.hpp"
#define MAX 100000000
using namespace std;

void testSearch(void){
    vector<int> v(MAX);
    for(int i=0; i<MAX; i++)
        v[i] = rand();
    sort(v.begin(), v.end());
    searching<int> searchClass;
    searchClass.compare(&searching<int>::binary, &searching<int>::linear, v, v[MAX/3]);
}

void testSort(void){
    vector<int> v(MAX);
    for(int i=0; i<MAX; i++)
        v[i] = rand();
    sorting<int> sortClass;
    sortClass.compare(&sorting<int>::quickSort, &sorting<int>::heapSort, v);
    //cout << is_sorted(result.begin(), result.end()) << endl;
    //sortClass.printArray();
}

int main(void){
    testSearch();
    testSort();
    return 0;
}