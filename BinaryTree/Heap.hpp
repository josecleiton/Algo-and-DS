#ifndef _HEAP_HPP
#define _HEAP_HPP
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
using namespace std;

namespace binary_tree{

template<typename ValueType, typename _Compare = std::greater<ValueType> >
class Heap{
    protected:
        vector<ValueType> values;
        _Compare key_compare;
    public:
        //typedef function<bool(const ValueType&, const ValueType&) > compare;
        
        Heap(_Compare __comp = std::greater<ValueType>() ){
            key_compare = __comp;
        }

        void push(ValueType K){
            values.push_back(K);
            heapifyDown();
        }

        ValueType pop(void){
            ValueType root = values[0];
            swap(values[0], values[values.size()-1]);
            values.pop_back();
            heapifyUp();
            return root;
        }

        void print(){
            for(auto item: values)
                cout << item << " ";
            cout << endl;
        }

    protected:
        // AJUSTA O ULTIMO (DEPOIS DA INSERÇÃO)
        void heapifyDown(void){
            int index = values.size()-1;
            const ValueType element = values[index];
            int parent, left, right;
            while(index > 0){
                parent = static_cast<int>(floor((index-1)/2));
                if(key_compare(values[index], values[parent])){
                    swap(values[index], values[parent]);
                    index = parent;
                }
                else break;
            }
        }
        // AJUSTA O PRIMEIRO (APÓS UMA REMOÇÃO)
        void heapifyUp(){
            int i = 0, left, right;
            const int heapsize = values.size();
            while(i < heapsize){
                left = 2*i+1;
                right = left+1;
                if(left >= heapsize or right >= heapsize) break;
                if(key_compare(values[left], values[i]) and key_compare(values[right], values[i])){
                    if(key_compare(values[left], values[right])){
                        swap(values[left], values[i]);
                        i = left;
                    }
                    else{
                        swap(values[right], values[i]);
                        i = right;
                    }
                }
                else if(key_compare(values[left], values[i])){
                    swap(values[left], values[i]);
                    i = left;
                }
                else if(key_compare(values[right], values[i])){
                    swap(values[right], values[i]);
                    i = right;
                }
            }
        }

};

}

#endif //_HEAP_HPP