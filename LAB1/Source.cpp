#include<iostream>
#include<time.h>
#include <chrono>
using namespace std;

int mergeSort(int* arr, int low, int high);
int merge(int* arr, int lowLeft, int highLeft, int lowRight, int highRight);
int mergeSortHybrid(int* arr, int low, int high, int s);
int insertionSort(int* arr, int low, int high);
int* generateArr(int size, int high);
int* generateCopy(int* arr, int size);
bool isSorted(int* arr, int size);
long fibonacci(unsigned n);

int main() {
	int S = 21;
	int keyComparisons = 0;
	int size = 100;
	cout << "Testing With fixed S = " << S << endl;
	for (int i = 0; i < 5; i ++) {
		size = size * 10;
		int* arr = generateArr(size, 1000000);
		keyComparisons = mergeSortHybrid(arr, 0, size - 1, S);
		//keyComparisons = mergeSort(arr, 0, size - 1);
		if (isSorted(arr, size) == false)
			cout << "Array was not sorted\n";
		cout << "Array size: " << size << endl;
		cout << "Key comparisons: " << keyComparisons << endl;
		delete[] arr;
	}

	size = size / 10;
	cout << "Testing same array and with Fixed N = " << size << endl;
	int* arr = generateArr(size, 1000000);
	int startS = 0;
	for (int i = 4; i <= 24; i+=2) {
		startS = i;
		int* arrCopy = generateCopy(arr, size);
		keyComparisons = mergeSortHybrid(arrCopy, 0, size - 1, startS);
		if (isSorted(arrCopy, size) == false)
			cout << "Array was not sorted\n";
		cout << "S is : " << startS << endl;
		cout << "Key comparisons: " << keyComparisons << endl;
	}
	delete[] arr;


	int keyComparisons2 = 0;
	cout << "Comparing Mergesort with MergeSort hybrid" << endl;
	size = size * 10;
	arr = generateArr(size, 1000000);
	int* arr2 = generateCopy(arr, size);
	keyComparisons = mergeSortHybrid(arr, 0, size - 1, S);
	keyComparisons2 = mergeSort(arr2, 0, size - 1);
	if (isSorted(arr, size) == false)
		cout << "Array was not sorted\n";
	if (isSorted(arr2, size) == false)
		cout << "Array was not sorted\n";
	cout << "Array size: " << size << endl;
	cout << "Key comparisons using hybrid merge sort: " << keyComparisons << endl;
	cout << "Key comparisons using merge sort: " << keyComparisons2 << endl;
	delete[] arr;
	
	auto start = std::chrono::steady_clock::now();
    std::cout << "f(42) = " << fibonacci(42) << '\n';
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	return 0;
	
}

long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}


int mergeSort(int* arr, int low, int high) {
	int keyComparisons = 0;
	if (low < high) {
		int mid = (low + high) / 2;
		keyComparisons = mergeSort(arr, low, mid);
		keyComparisons += mergeSort(arr, mid + 1, high);
		keyComparisons += merge(arr, low, mid,mid+1, high);
	}
	return keyComparisons;
}
int merge(int* arr, int lowLeft, int highLeft, int lowRight, int highRight) {
	int keyComparisons = 0;
	int lowLeftCopy = lowLeft;
	int start = 0;
	int* temp = new int[highRight - lowLeft+1];


	while (lowLeft <= highLeft && lowRight <= highRight) {
		if (arr[lowLeft] < arr[lowRight]) {
			temp[start] = arr[lowLeft];
			lowLeft++;
			
		}

		else {
			temp[start] = arr[lowRight];
			lowRight++;
		}
		keyComparisons++;
		start++;
	}

	while (lowLeft <= highLeft) {
		temp[start] = arr[lowLeft];
		lowLeft++;
		start++;
	}
	while (lowRight <= highRight) {
		temp[start] = arr[lowRight];
		lowRight++;
		start++;
	}

	for (int i = 0; i < start; i++,lowLeftCopy++) {
		arr[lowLeftCopy] = temp[i];
	}
	return keyComparisons;
}
int mergeSortHybrid(int* arr, int low, int high, int s) {
	int keyComparisons = 0;
	if (high - low <= s) {
		return insertionSort(arr, low, high);
	}
	else {
		int mid = (low + high) / 2;
		keyComparisons += mergeSortHybrid(arr, low, mid,s);
		keyComparisons += mergeSortHybrid(arr, mid + 1, high,s);
		keyComparisons += merge(arr, low, mid, mid + 1, high);
	}
	return keyComparisons;
}
int insertionSort(int* arr, int low, int high) {
	int keyComparisons = 0;
	for (int i = low; i <= high; i++) {
		int current = arr[i];
		int j = i - 1;
		while (j >= low && arr[j] > current) {
			arr[j + 1] = arr[j];
			j--;
			keyComparisons++;
		}
		keyComparisons++;
		arr[j+1] = current;
	}
	return keyComparisons;
}

int* generateArr(int size, int high) {
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % high + 1;
	}
	return arr;
}

int* generateCopy(int* arr, int size) {
	int* newArr = new int[size];
	for (int i = 0; i < size; i++)
		newArr[i] = arr[i];
	return newArr;
}

bool isSorted(int* arr, int size) {
	for (int i = 0; i < size-1; i++) {
		if (arr[i] > arr[i + 1])
			return false;
	}
	return true;
}