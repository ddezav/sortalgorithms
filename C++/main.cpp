#include <cstdlib>
#include <iostream>
#include <time.h>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;


// -------mergesort begin
// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int array[], int const left, int const mid,
		int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays
	auto *leftArray = new int[subArrayOne],
		*rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne
		= 0, // Initial index of first sub-array
		indexOfSubArrayTwo
		= 0; // Initial index of second sub-array
	int indexOfMergedArray
		= left; // Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne
		&& indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne]
			<= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray]
				= leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray]
				= rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray]
			= leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray]
			= rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

// UTILITY FUNCTIONS
// Function to print an array
void printArray(double A[], int size)
{
	int i=0;
	for (i = 0; i < size-1; i++)
		cout <<  A[i] << "\t";
	cout<< A[size-1]<<endl;
}
void createCsv(int x[], int sizex,double A[], int sizeA, string nameFile, int veces)
{
	fstream fout;
	fout.open(nameFile, ios::out | ios::app);
	int i=0;
	int k=0;
	fout << x[k]<<"\t ";
	k++;
	for (i = 0; i < sizeA; i++){
		fout << A[i];
		if((i+1)%veces==0){
			fout << endl;
			if(k<=sizex-1){
				fout << x[k]<<"\t";
				k++;
			}			
		}else{
			fout << ", ";
		}
	}
}


// -------mergesort finish

// -------quicksort begin

int partition(int arr[], int start, int end)
{
  int i = start+1, j = end;
  if(start!=end && start<end){
    int pivot = arr[start];
    // Sorting left and right parts of the pivot element
    while (i <= j){
      if(arr[i]>pivot && arr[j] < pivot){
        swap(arr[i],arr[j]);
      }
      if(!(arr[i]>pivot)){
        i=i+1;
      }
      if(!(arr[j]<pivot)){
        j=j-1;
      }
    }
  }
	
  swap(arr[start],arr[j]);
  return j;
}

void quickSort(int arr[], int start, int end)
{

	// base case
	if (start >= end)
		return;

	// partitioning the array
	int p = partition(arr, start, end);

	// Sorting the left part
	quickSort(arr, start, p - 1);

	// Sorting the right part
	quickSort(arr, p + 1, end);
}
// ------------quicksort finish

// ------------heapsort begin

// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(int arr[], int N, int i)
{

	// Initialize largest as root
	int largest = i;

	// left = 2*i + 1
	int l = 2 * i + 1;

	// right = 2*i + 2
	int r = 2 * i + 2;

	// If left child is larger than root
	if (l < N && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest
	// so far
	if (r < N && arr[r] > arr[largest])
		largest = r;

	// If largest is not root
	if (largest != i) {
		swap(arr[i], arr[largest]);
		// Recursively heapify the affected
		// sub-tree
		heapify(arr, N, largest);
	}
}

// Main function to do heap sort
void heapSort(int arr[], int N)
{

	// Build heap (rearrange array)
	for (int i = N / 2 - 1; i >= 0; i--)
		heapify(arr, N, i);

	// One by one extract an element
	// from heap
	for (int i = N - 1; i > 0; i--) {

		// Move current root to end
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}
// ------------- heapsort finish
// ------------- insertionsort begin
void insertionSort(int arr[], int n) 
{ 
    int i, key, j; 
    for (i = 1; i < n; i++)
    { 
        key = arr[i]; 
        j = i - 1; 
        while (j >= 0 && arr[j] > key)
        { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 
} 
// ------------------- insertionsort finish
int* randArray(int size){
  auto const CSIZE = size;
	auto *arr = new int[CSIZE];
  for(int i=0;i<size;i++)
    arr[i]=rand()%size;  //Generate number between 0 to 99
  
  return arr;
}
int main(){
  int i=0,j=0,k=0,veces=10;  
  int datax[] = {5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000 ,50000, 60000,70000,80000};
  int *unsorted;
  auto datax_size = sizeof(datax) / sizeof(datax[0]);

  double times_merge[datax_size*veces];
  double times_quick[datax_size*veces];
  double times_heap[datax_size*veces];
	double times_insertion[datax_size*veces];

  int size_t;
  double time_merge, time_heap, time_quick,time_insertion;
  for(i=0;i<datax_size;i++){
		for(j=0;j<veces;j++){
			size_t = datax[i];
    	unsorted = randArray(size_t);
    	auto start_merge = chrono::high_resolution_clock::now();
    	mergeSort(unsorted, 0, size_t - 1);
    	auto end_merge = chrono::high_resolution_clock::now();
    	time_merge = chrono::duration_cast<chrono::nanoseconds>(end_merge - start_merge).count();
    	times_merge[k] = time_merge*1e-9;
  
    	unsorted = randArray(size_t);
    	auto start_quick = chrono::high_resolution_clock::now();
    	quickSort(unsorted, 0, size_t - 1);
    	auto end_quick = chrono::high_resolution_clock::now();
    	time_quick = chrono::duration_cast<chrono::nanoseconds>(end_quick - start_quick).count();
    	times_quick[k] = time_quick*1e-9;

    	unsorted = randArray(size_t);
    	auto start_heap = chrono::high_resolution_clock::now();
    	heapSort(unsorted, size_t);
    	auto end_heap = chrono::high_resolution_clock::now();
    	time_heap = chrono::duration_cast<chrono::nanoseconds>(end_heap - start_heap).count();
    	times_heap[k] = time_heap*1e-9;

			
    	unsorted = randArray(size_t);
    	auto start_insertion = chrono::high_resolution_clock::now();
			insertionSort(unsorted, size_t);
			auto end_insertion = chrono::high_resolution_clock::now();
    	time_insertion= chrono::duration_cast<chrono::nanoseconds>(end_heap - start_heap).count();
    	times_insertion[k] = time_insertion*1e-9;

			k++;
		}    
  }
  //printArray(times_heap,datax_size*veces);
  //printArray(times_merge,datax_size*veces);
  //printArray(times_quick,datax_size*veces);
  
	createCsv(datax, datax_size,times_heap, datax_size*veces, "cppheap.csv",veces);
	createCsv(datax, datax_size,times_merge, datax_size*veces, "cppmerge.csv",veces);
	createCsv(datax, datax_size,times_quick, datax_size*veces, "cppquick.csv",veces);
	createCsv(datax, datax_size,times_insertion, datax_size*veces, "cppinsertion.csv",veces);

}
  
