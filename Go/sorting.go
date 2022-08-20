package main

import (
	"fmt"
	"math/rand"
	"time"
	"strconv"
	"io/ioutil"
	"strings"
	"os"
)

func mergeSort(items []int) []int {
    // Si el array contiene uno o dos elementos se considera ordenado
	if len(items) < 2 {
        return items
    }

	// Se divide el array de elementos en dos mitades y se ordena cada mitad
    first := mergeSort(items[:len(items)/2])
    second := mergeSort(items[len(items)/2:])

	// Se copian los datos a un array temporal de menor a mayor
	arr := []int{}
    i := 0
    j := 0
    for i < len(first) && j < len(second) {
        if first[i] < second[j] {
            arr = append(arr, first[i])
            i++
        } else {
            arr = append(arr, second[j])
            j++
        }
    }

	// Se verifica si despues de copiar los datos al temporal se dejo alguno si copiar
    for ; i < len(first); i++ {
        arr = append(arr, first[i])
    }
    for ; j < len(second); j++ {
        arr = append(arr, second[j])
    }

    return arr
}

func partition(arr []int, low, high int) ([]int, int) {
	pivot := arr[high]
	i := low
	for j := low; j < high; j++ {
		if arr[j] < pivot {
			arr[i], arr[j] = arr[j], arr[i]
			i++
		}
	}
	arr[i], arr[high] = arr[high], arr[i]
	return arr, i
}

func quickSort(arr []int, low, high int) []int {
	if low < high {
		var p int
		arr, p = partition(arr, low, high)
		arr = quickSort(arr, low, p-1)
		arr = quickSort(arr, p+1, high)
	}
	return arr
}

func maxHeapify(tosort []int, position int) {
    size := len(tosort)
    maximum := position
    leftChild := 2*position + 1
    rightChild := leftChild + 1
    if leftChild < size && tosort[leftChild] > tosort[position] {
        maximum = leftChild
    }
    if rightChild < size && tosort[rightChild] > tosort[maximum] {
        maximum = rightChild
    }

    if position != maximum {
        tosort[position], tosort[maximum] = tosort[maximum], tosort[position]
        maxHeapify(tosort, maximum) //recursive
    }
}

func heapSort(tosort []int) []int {
    for i := (len(tosort) - 1) / 2; i >= 0; i-- {
        maxHeapify(tosort, i)
    }
    for i := len(tosort) - 1; i >= 1; i-- {
        tosort[i], tosort[0] = tosort[0], tosort[i]
        maxHeapify(tosort[:i-1], 0)
    }

    return tosort
}

func insertionsort(items []int) {
    var n = len(items)
    for i := 1; i < n; i++ {
        j := i
        for j > 0 {
            if items[j-1] > items[j] {
                items[j-1], items[j] = items[j], items[j-1]
            }
            j = j - 1
        }
    }
}

func main() {
    var numbers [][]int
	rand.Seed(time.Now().UnixNano())


	b, err := ioutil.ReadFile("../data/data.txt")
    if err != nil { panic(err) }

	lines := strings.Split(string(b), "\n")

	for i:=0;i<len(lines);i++{
		words := strings.Split(string(lines[i]), " ")
		temp := make([]int, 0)
		for j:=0;j<len(words);j++{
			if len(words[j]) > 0{
				i,err :=strconv.ParseInt(words[j],10,0)
				if err != nil {
					panic(err)
				}
				temp = append(temp,int(i))
			}
		}
		if len(temp) > 0 {
			numbers = append(numbers, [][]int{temp}...)
		}
	}

	// Escribimos un archivo con los tiempos de ejecución para cada algoritmo
	GH, errGH := os.Create("GH.csv")
	if errGH != nil {
        panic(errGH)
    }
	defer GH.Close()
	GM, errGM := os.Create("GM.csv")
	if errGM != nil {
        panic(errGM)
    }
	defer GM.Close()
	GQ, errGQ := os.Create("GQ.csv")
	if errGQ != nil {
        panic(errGQ)
    }
	defer GQ.Close()
	GI, errGI := os.Create("GI.csv")
	if errGI != nil {
        panic(errGI)
    }
	defer GI.Close()

	veces := 10

	for i:=0;i<len(numbers);i++{
		fmt.Printf("Longitud: %v ----------------------------\n",len(numbers[i]))
		
		GH.WriteString(strconv.Itoa(len(numbers[i])))
		GM.WriteString(strconv.Itoa(len(numbers[i])))
		GQ.WriteString(strconv.Itoa(len(numbers[i])))
		GI.WriteString(strconv.Itoa(len(numbers[i])))

		// HEAPSORT
		prom := 0
		for k:=0;k<veces;k++{
			unsorted := make([]int, len(numbers[i]))
			copy(unsorted,numbers[i])

			time1 := time.Now()
			heapSort(unsorted)
			time2 := time.Now()
			tiempo := time2.Sub(time1)
			GH.WriteString("\t")
			prom += int(tiempo.Microseconds())
			GH.WriteString(strconv.Itoa(int(tiempo.Microseconds())))
		}
		prom = prom / veces
		fmt.Printf("HeapSort: \t%v\n",prom)

		// MERGESORT
		prom = 0
		for k:=0;k<veces;k++{
			unsorted := make([]int, len(numbers[i]))
			copy(unsorted,numbers[i])

			time1 := time.Now()
			mergeSort(unsorted)
			time2 := time.Now()
			tiempo := time2.Sub(time1)
			GM.WriteString("\t")
			prom += int(tiempo.Microseconds())
			GM.WriteString(strconv.Itoa(int(tiempo.Microseconds())))
		}
		prom = prom / veces
		fmt.Printf("MergeSort: \t%v\n",prom)

		// QUICKSORT
		prom = 0
		for k:=0;k<veces;k++{
			unsorted := make([]int, len(numbers[i]))
			copy(unsorted,numbers[i])

			time1 := time.Now()
			quickSort(unsorted,0,len(unsorted)-1)
			time2 := time.Now()
			tiempo := time2.Sub(time1)
			GQ.WriteString("\t")
			prom += int(tiempo.Microseconds())
			GQ.WriteString(strconv.Itoa(int(tiempo.Microseconds())))
		}
		prom = prom / veces
		fmt.Printf("QuickSort: \t%v\n",prom)

		// INSERTIONSORT
		prom = 0
		for k:=0;k<veces;k++{
			unsorted := make([]int, len(numbers[i]))
			copy(unsorted,numbers[i])

			time1 := time.Now()
			insertionsort(unsorted)
			time2 := time.Now()
			tiempo := time2.Sub(time1)
			GI.WriteString("\t")
			prom += int(tiempo.Microseconds())
			GI.WriteString(strconv.Itoa(int(tiempo.Microseconds())))
		}
		prom = prom / veces
		fmt.Printf("InsertionSort: \t%v\n",prom)
		
		
		GH.WriteString("\n")
		GM.WriteString("\n")
		GQ.WriteString("\n")
		GI.WriteString("\n")
	}
    
    
}