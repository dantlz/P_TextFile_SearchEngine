#include <vector>
#include <cmath>
#include <iostream>

template <class T, class Comparator>
void mergeRecursion(std::vector<T> &a, int l, int r, Comparator comp){
    if (l<r) { // otherwise, just one element, which is sorted
        int m = floor((l+r)/2);
        mergeRecursion(a, l, m, comp);
        mergeRecursion(a, m+1, r,comp);
        Merge(a, l, r, m,comp); // this is a separate function given below
    }
}

template <class T, class Comparator>
void Merge (std::vector<T> &a, int l, int r, int m, Comparator comp){
    T temp[r+1-l];
    // trace through the two subarrays, copying into a temporary one
    int i = l;
    int j = m+1;
    int k = 0;
    while (i <= m || j <= r){  // at least one subarray contains another element
        //if (i <= m && (j > r || a[i] <= a[j])){ // next smallest element in left subarray
        if (i <= m && (j > r || comp(a[i],a[j]))){ // next smallest element in left subarray
            temp[k] = a[i]; 
            i ++; 
            k ++; 
        }
        else { // next smallest element in right subarray
            temp[k] = a[j]; 
            j ++; 
            k ++; 
        }    
    }
    // now copy over the merged array into the original
    for (k = 0; k < r+1-l; k ++)
        a[k+l] = temp[k];
}

template <class T, class Comparator>
void mergeSort (std::vector<T> &myArray, Comparator comp){
	if(myArray.size()<2)
		return;
	int low = 0;
	int high=myArray.size() - 1;
	mergeRecursion(myArray,low,high,comp);
}