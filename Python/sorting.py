from math import log       # import done only to use logarithm
import numpy as np         # import done to use of calculation, arrays
import matplotlib.pyplot as plt   # import done only to use graphics
import datetime
import time
from numpy.random import seed
from numpy.random import rand

import sys

def insertionSort(b):
    for i in range(1, len(b)):
        up = b[i]
        j = i - 1
        while j >= 0 and b[j] > up: 
            b[j + 1] = b[j]
            j -= 1
        b[j + 1] = up     
    return b   

def mergeSort(arr):
    if len(arr) > 1:
 
         # Finding the mid of the array
        mid = len(arr)//2
 
        # Dividing the array elements
        L = arr[:mid]
 
        # into 2 halves
        R = arr[mid:]
 
        # Sorting the first half
        mergeSort(L)
 
        # Sorting the second half
        mergeSort(R)
 
        i = j = k = 0
 
        # Copy data to temp arrays L[] and R[]
        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1
 
        # Checking if any element was left
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1
 
        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

# Function to find the partition position
def partition(arr, l, h):
    low, high = l, h
    if l != h and l < h:
        # Choose the leftmost element as pivot
        pivot = arr[l]
        low = low+1
        # Traverse through all elements
        # compare each element with pivot
        while low <= high:
            if arr[high] < pivot and arr[low] > pivot:
                arr[high], arr[low] = arr[low], arr[high]
            if not arr[low] > pivot:
                low += 1
            if not arr[high] < pivot:
                high -= 1
    arr[l], arr[high] = arr[high], arr[l]
    # Return the position from where partition is done
    return high
  
# Function to perform quicksort
def quick_sort(array, low, high):
    if low < high:
    
        # Find pivot element such that
        # element smaller than pivot are on the left
        # element greater than pivot are on the right
        pi = partition(array, low, high)

        # Recursive call on the left of pivot
        quick_sort(array, low, pi - 1)

        # Recursive call on the right of pivot
        quick_sort(array, pi + 1, high)

def heapify(arr, N, i):
    largest = i  # Initialize largest as root
    l = 2 * i + 1     # left = 2*i + 1
    r = 2 * i + 2     # right = 2*i + 2
 
    # See if left child of root exists and is
    # greater than root
    if l < N and arr[largest] < arr[l]:
        largest = l
 
    # See if right child of root exists and is
    # greater than root
    if r < N and arr[largest] < arr[r]:
        largest = r
 
    # Change root, if needed
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]  # swap
 
        # Heapify the root.
        heapify(arr, N, largest)
 
# The main function to sort an array of given size
 
 
def heapSort(arr):
    N = len(arr)
 
    # Build a maxheap.
    for i in range(N//2 - 1, -1, -1):
        heapify(arr, N, i)
 
    # One by one extract elements
    for i in range(N-1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]  # swap
        heapify(arr, i, 0)

seed(1)
# generate random numbers between 0-1
def pruebaIteracion(numero,dataInsert,dataMerge,dataQuick,dataHeap):
  dataMerge = [numero]
  dataQuick = [numero]
  dataInsert = [numero]
  dataHeap = [numero]
  data = np.ones(nDatos) * numero 

  data = data.astype(int)     

 
  for i in data:
    arr = rand(i)
    t = time.time()
    arr1 = arr
    insertionSort(arr1)
    fin = time.time() -t 
    dataInsert.append(fin)
  for i in data:
    arr = rand(i)
    arr1 = arr
    t = time.time()
    mergeSort(arr1)
    fin = time.time() -t 
    dataMerge.append(fin)


    sys.setrecursionlimit(3000)


  for i in data:
    arr = rand(i)

    t = time.time()
    quick_sort(arr,0, len(arr) - 1)
    fin = time.time() -t 
    dataQuick.append(fin)
  for i in data:
    arr = rand(i)

    t = time.time()
    heapSort(arr)
    fin = time.time() -t 
    dataHeap.append(fin)

  
  return dataInsert,dataMerge,dataQuick,dataHeap

seed(1)

# generate random numbers between 0-1
i = 0
dMergeTot = []
dQuickTot = []
dInsertTot = []
dHeapTot = []
nDatos = 10
dataNumeros =[5000,6000,7000,8000,9000,10000,20000,30000,40000,50000,60000,70000,80000]
for x in dataNumeros:
  dataMerge = []
  dataQuick = []
  dataInsert = []
  dataHeap = []

  dataInsert,dataMerge,dataQuick,dataHeap = pruebaIteracion(x,dataInsert,dataMerge,dataQuick,dataHeap)
  
  dMergeTot.append(dataMerge)
  dQuickTot.append(dataQuick)
  dInsertTot.append(dataInsert)
  dHeapTot.append(dataHeap)
  i = i + 1
np.set_printoptions(suppress=True)
dMerge=np.array(dMergeTot)
dQuick=np.array(dQuickTot)
dInsert=np.array(dInsertTot)
dHeap=np.array(dHeapTot)
print (dMerge.shape)
list =  [1, 2, 3, 4, 5, 6]
dMergeProm = []
dQuickProm = []
dInsertProm = []
dHeapProm = []

np.savetxt("PM.csv",  dMerge , delimiter="\t" , fmt='%.5f')
np.savetxt("PQ.csv",  dQuick , delimiter="\t" , fmt='%.5f')
np.savetxt("PI.csv",  dInsert , delimiter="\t" , fmt='%.5f')
np.savetxt("PH.csv",  dHeap , delimiter="\t" , fmt='%.5f')