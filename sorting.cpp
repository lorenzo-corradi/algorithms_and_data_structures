#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void quicksort(std::vector<int>& vec, uint left, uint right) {
    
    uint i = left, j = right;
    uint pivot = (left + right) / 2;
    int temp;
    
    while (i <= j) {
        
        while (vec[i] < pivot)
            ++i;
            
        while (vec[j] > pivot)
            --j;
        
        if (i <= j) {
            temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
            ++i;
            --j;
        }
        
    };
    
    if (left < j)
        quicksort(vec, left, j);
        
    if (i < right)
        quicksort(vec, i, right);
    
};


void mergesort(std::vector<int>& vec, std::vector<int>::iterator left, std::vector<int>::iterator right) {
    
    if (left >= right)
        return;
    
    std::vector<int>::iterator medium = left + (right - left) / 2;
    
    mergesort(vec, left, medium);
    mergesort(vec, medium + 1, right);
    
    std::inplace_merge(left, medium, right);
    
}


int main()
{
    vector<int> vec {1, 2, 3};
    vec.reserve(10);
    vec.push_back(2);
    vec.push_back(5);
    vec.push_back(-1);
    
    
        
    for (int i : vec) {
        cout << i << " ";
    }
    
    cout << endl;
        
    mergesort(vec, vec.begin(), vec.end());
    
    for (int i : vec) {
        cout << i << " ";
    }
    
    return 0;
}
