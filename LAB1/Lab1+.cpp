#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <iterator>
#include <numeric>
#include <string>
#include <random>
#include <fstream>

using namespace std;
using std::cout;

bool isSorted(int* arr, int size) {
	for (int i = 0; i < size-1; i++) {
		if (arr[i] > arr[i + 1])
			return false;
	}
	return true;
}

void generate_arrays(int high, int* arrays, int size){
    for (int i = 0; i < size; i++) {
		arrays[i] = rand() % high + 1;
	}
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
int hybrid_sort(int* array, int S, int n, int m){
    int keycomparisons = 0;
    if(m - n + 1 <= S){
        for(int i = n; i <= m; i++){
            for(int j = i; j > n; j--){
                keycomparisons++;
                if(array[j] < array[j - 1]){
                    int temp = array[j];
                    array[j] = array[j - 1];
                    array[j-1] = temp;
                }
                else    break;
            }
        }
    }else if(m - n  > 0){
        int mid = (n + m) / 2;
        keycomparisons += hybrid_sort(array, S, n, mid);
        keycomparisons += hybrid_sort(array, S, mid + 1, m);
        keycomparisons += merge(array, n, mid, mid+1, m);
    }
    return keycomparisons;
}

int mergeSort(int* array, int n, int m){
    int keycomparisons = 0;
    if(m - n > 0){
        int mid = (n + m) / 2;
        keycomparisons += mergeSort(array, n, mid);
        keycomparisons += mergeSort(array, mid + 1, m);
        keycomparisons += merge(array, n, mid, mid+1, m);
    }
    return keycomparisons;
}

int main(){
    const int x = 100000;
    int* array = new int[x];
    for (int i = 0; i < x; i++) *(array+i) = rand() % x + 1;

    ofstream ofs("resultConst.csv");
   
    cout << "【 MergeInsertion Sort 】\n" << endl;
    double fastest = 10.00000;
    int sindex;
    for(int S=1;S<=100;S++){
        int* arrays = new int[x];
        copy(array, array+x, arrays);
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

        int kc = hybrid_sort(arrays, S, 0, x-1);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end-start;
        if(!isSorted(arrays, x)) cout << "S: " << S << "Not Sorted!" << endl;
        if(fastest>elapsed.count()){
            sindex = S;
            fastest = elapsed.count();
        }

        delete []arrays;
    }
    

   /*
    cout << "【 MergeInsertion Sort 】\n" << endl;
    ofs << "MI" << endl;
    for(x=1000;x<=10000000;x*=10){
        int kc = 0;
        int* arrays = new int[x];
        copy(array, array+x, arrays);
        auto start = std::chrono::steady_clock::now();

        kc = hybrid_sort(arrays, S, 0, x-1, x);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end-start;
        cout << "Testing with S = " << S << endl;
        cout << "Array size: " << x << endl;
        cout << "Key Comparisons: " << kc << endl;
        cout << "Elapsed time: " << elapsed.count() << "s\n" << endl;

        ofs << x << ", " << kc << ", " << elapsed.count() << endl;
    }
    */

    /*
    cout << "【 Original Merge Sort 】\n" << endl;
    ofs << "Merge" << endl;
    for(int x=1000;x<=10000000;x*=10){
        int kc = 0;
        int* arrays = new int[x];
        copy(array, array+x, arrays);
        auto start = std::chrono::steady_clock::now();

        kc = mergeSort(arrays, 0, x - 1);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end-start;
        cout << "Array size: " << x << endl;
        cout << "Key Comparisons: " << kc << endl;
        cout << "Elapsed time: " << elapsed.count() << "s\n" << endl;

        ofs << x << ", " << kc << ", " << elapsed.count() << endl;
   }*/

    cout << "Comparing HybridSort with MergeSort" << endl;
    cout << "Array size: " << x << endl;
    cout << "S: " << sindex << endl;

    int* arrays = new int[x];
    copy(array, array+x, arrays);
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    int kc = hybrid_sort(arrays, sindex, 0, x-1);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end-start;

    delete []arrays;

    cout << "Key Comparisons using HybridSort: " << kc << endl;
    cout << "Elapsed time: " << elapsed.count() << "s" << endl;
    arrays = new int[x];
    copy(array, array+x, arrays);
    start = chrono::steady_clock::now();

    kc = mergeSort(arrays, 0, x - 1);

    end = std::chrono::steady_clock::now();
    elapsed = end-start;
    //cout << "Array size: " << x << endl;
    cout << "Key Comparisons using MergeSort: " << kc << endl;
    cout << "Elapsed time: " << elapsed.count() << "s\n" << endl;

    delete []arrays;
}