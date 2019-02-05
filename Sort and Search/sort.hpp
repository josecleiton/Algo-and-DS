#ifndef _SORT_H
#define _SORT_H

#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

template <class ValueType>
class sorting{
protected:
    vector<ValueType>* lastResult{};
public:
    typedef vector<ValueType> (sorting<ValueType>::*sortFunc_t)(vector<ValueType>);

    // O(N) IN BEST CASE BUT O(N^2) WORST AND AVERAGE
    // O(1) SPACE COMPLEXITY
    vector<ValueType> bubbleSort(vector<ValueType> array){
        bool noSwap = false;
        for(int i=array.size()-1; i>0 and !noSwap; i--){
            noSwap = true;
            for(int j=0; j<i; j++){
                if(array[j] > array[j+1]){
                    swap(array[j], array[j+1]);
                    noSwap = false;
                }
            }
        }
        return array;
    }

    vector<ValueType> selectionSort(vector<ValueType> array){
        int lowest;
        for(int i=0; i<array.size(); i++){
            lowest = i;
            for(int j=i+1; j<array.size(); j++)
                if(array[j] < array[lowest])
                    lowest = j;
            swap(array[i], array[lowest]);
        }
        return array;
    }

    // O(N) BEST CASE BUT O(N^2) WORST AND AVERAGE
    // O(1) SPACE COMPLEXITY
    vector<ValueType> insertionSort(vector<ValueType> array){
        ValueType k;
        int i, j;
        for(i=0; i<array.size(); i++){
            k = array[i];
            for(j=i-1; j>=0 and array[j] > k; j--)
                array[j+1] = array[j];
            array[j+1] = k;
        }
        return array;
    }

    // O(NlogN) RUN COMPLEXITY
    // O(N) SPACE COMPLEXITY
    vector<ValueType> mergeSort(vector<ValueType> array){
        if(array.size() <= 1)
            return array;
        int64_t middle = array.size()/2;
        auto left = mergeSort(vector<ValueType>(array.begin(), array.begin()+middle));
        auto right = mergeSort(vector<ValueType>(array.begin()+middle+1 , array.end()));
        return merge(left, right);
    }

private:
    vector<ValueType> merge(vector<ValueType> v1, vector<ValueType> v2){
        vector<ValueType> result(v1.size()+v2.size());
        int i, j, k;
        i = j = k = 0;
        while(i < v1.size() and j < v2.size()){
            if(v1[i] < v2[j])
                result[k++] = v1[i++];
            else if(v1[i] > v2[j])
                result[k++] = v2[j++];
            else
                result[k++] = v2[i++] - (j++*0);
        }
        if(i < v1.size())
            for(int it = i; it < v1.size(); it++)
                result[k++] = v1[it];
        else if(j < v2.size())
            for(int it = j; it < v2.size(); it++)
                result[k++] = v2[it];
        return result;
    }

public:
    // O(NlogN) RUN COMPLEXITY but O(N^2) WORST CASE
    // O(NlogN) SPACE COMPLEXITY
    // PIVOT = LAST ITEM IN ARRAY
    vector<ValueType> quickSort(vector<ValueType> array){
        quickRec(array, 0, array.size()-1);
        return array;
    }

private:
    int64_t pivot(vector<ValueType>& array, int64_t low, int64_t high){
        ValueType pivot = array[high];
        int64_t i = low-1;
        for(int64_t j=low; j<=high-1; j++){
            if(array[j] <= pivot){
                i++;
                swap(array[i], array[j]);
            }
        }
        swap(array[i+1], array[high]);
        return i+1;
    }

    void quickRec(vector<ValueType>& array, int64_t low, int64_t high){
        if(low < high){
            int64_t pivotIndex = pivot(array, low, high);
            quickRec(array, low, pivotIndex-1);
            quickRec(array, pivotIndex+1, high);
        }
    }

    // O(N*K) RUN COMPLEXITY
    // O(N+10) (JUST O(N)) SPACE COMPLEXITY (0-9 DIGITS)
public:
    vector<int> radixSort(vector<int> array){
        int limit = maxDigits(array);
        vector<int> result(array.size());
        vector<vector<int> > buckets(10); // 0 - 9 DIGITS
        int kdigit, j;
        for(int k=0; k<limit; k++){
            if(k){
                for(auto& vet: buckets) // RESET ALL BUCKETS
                    vet.clear();
            }
            for(int i=0; i<array.size(); i++){
                kdigit = getDigit(array[i], k);
                buckets[kdigit].push_back(array[i]); // PUT THE INTEGERS IN BUCKETS
            }
            result.clear();
            j=0;
            for(auto& vet: buckets)
                for(auto& it: vet)
                    result[j++] = it; // PUT THE BUCKETS IN AN AUXILIAR ARRAY (INPUT ISN'T MODIFIED)
        }
        return result;
    }

private:
    int getDigit(int num, int k){
        return ((int)floor(num/pow(10, k)))%10;
    }

    int digitCount(int num){
        if(!num) return 1;
        return floor(log10(num))+1;
    }
    
    int maxDigits(vector<int>& vet){
        int result = 0;
        for(auto i: vet)
            result = max(result, digitCount(i));
        return result;
    }

public:
    // O(N+K) RUN COMPLEXITY
    // O(K) SPACE COMPLEXITY
    // CAREFUL WITH THE LARGEST ELEMENT IN ARRAY (IF IS TOO LARGE MAY CRASH)
    vector<int> countingSort(vector<int> array){
        int largest = *max_element(array.begin(), array.end()), i;
        vector<int> temp(array.size());
        vector<int> count(largest+1);
        for(i=0; i<array.size(); i++)
            count[array[i]]++;
        for(i=1; i<=largest; i++)
            count[i] = count[i-1]+count[i];
        for(i=array.size()-1; i>=0; i--){
            temp[count[array[i]]-1] = array[i];
            count[array[i]]--;
        }
        return temp;
    }

private:
    void heapify(vector<ValueType>& array, int64_t tam, int64_t i){
        int64_t largest = i, left = 2*i+1, right = 2*i+2;
        if(left < tam and array[left] > array[largest])
            largest = left;
        if(right < tam and array[right] > array[largest])
            largest = right;
        if(largest != i){
            swap(array[i], array[largest]);
            heapify(array, tam, largest);
        }
    }

public:
    vector<ValueType> heapSort(vector<ValueType> array){
        long long tam = array.size();
        for(long long i=tam/2-1; i>=0; i--)
            heapify(array, tam, i);
        for(long long i=tam-1; i>=0; i--){
            swap(array[0], array[i]);
            heapify(array, i, 0);
        }
        return array;
    }

    void compare(sortFunc_t A, sortFunc_t B, vector<ValueType> vet){
        vector<ValueType> result;
        float timeA, timeB;
        clock_t clk = clock();
        result = (this->*A)(vet);
        clk = clock()-clk;
        timeA = ((float)clk)/CLOCKS_PER_SEC;
        printf("First method took %f seconds to run. Sort check: %d.\n", timeA, \
            is_sorted(result.begin(), result.end()));

        clk = clock();
        result = (this->*B)(vet);
        clk = clock()-clk;
        timeB = ((float)clk)/CLOCKS_PER_SEC;
        printf("Second method took %f seconds to run. Sort check: %d.\n", timeB, \
            is_sorted(result.begin(), result.end()));;
        if(timeA < timeB)
            puts("First method is faster.");
        else if(timeA > timeB)
            puts("Second method is faster.");
        else
            puts("Same run time.");
    }

    void setResult(vector<ValueType>& _v){
        lastResult = &_v;
    }

    // BEFORE USE PRINTARRAY CALL SETRESULT.
    void printArray(){
        if(lastResult != nullptr){
            cout << "Result= [";
            for(int i=0; i<lastResult->size(); i++){
                cout << (*lastResult)[i];
                if(i+1 < lastResult->size())
                    cout << ", ";
            }
            cout << "]" << endl;
            lastResult = nullptr;
        }
        else cout << "Vetor resultante vazio. " << endl;
    }
};

#endif
