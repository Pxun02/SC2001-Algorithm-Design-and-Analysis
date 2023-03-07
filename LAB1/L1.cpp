#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <numeric>
using namespace std;
using i64 = int64_t;

const i64 K = 5;
void insertionSort(i64* A, i64 p, i64 q) {
    for (i64 i = p; i < q; i++) {
        i64 tempVal = A[i + 1];
        i64 j = i + 1;
        while (j > p && A[j - 1] > tempVal) {
            A[j] = A[j - 1];
            j--;
        }
        A[j] = tempVal;
    }
    i64 temp[q + 1 - p];
    copy(A + p, A + q + 1, temp);
    for(i64 i: temp)    cout << i << " ";
    cout << endl;
    
    
}

void merge(i64* A, i64 p, i64 q, i64 r) {
    i64 n1 = q - p + 1;
    i64 n2 = r - q;
    i64 LA[q - p + 1];
    copy(A + p, A + q + 1, LA);
    i64 RA[r - q];
    copy(A + q + 1, A + r + 1, RA);
    i64 rIndex = 0;
    i64 lIndex = 0;
    for (i64 i = p; i < r - p + 1; i++) {
        if (rIndex == n2) {
            A[i] = LA[lIndex];
            lIndex++;
        } else if (lIndex == n1) {
            A[i] = RA[rIndex];
            rIndex++;
        } else if (RA[rIndex] > LA[lIndex]) {
            A[i] = LA[lIndex];
            lIndex++;
        } else {
            A[i] = RA[rIndex];
            rIndex++;
        }
    }
}

void mySort(i64* A, i64 p, i64 r) {
    if (r - p > K) {
        i64 q = (p + r) / 2;
        mySort(A, p, q);
        mySort(A, q + 1, r);
        merge(A, p, q, r);
    } else {
        insertionSort(A, p, r);
    }
}

int main() {
    i64 A[10];
    double elapsed[10];
    for(int lp=0;lp<10;lp++){
        for(i64 i=0;i<=9;i++)   A[i] = 10 - i;
        chrono::system_clock::time_point start, end;
        start = chrono::system_clock::now();

        mySort(A, 0, sizeof(A) / sizeof(i64) - 1);

        end = chrono::system_clock::now();
        elapsed[lp] = chrono::duration_cast<chrono::milliseconds>(end-start).count();
        for(i64 i: A)   cout << i << " ";
    }
    for(int lp=0;lp<100;lp++){
        cout << "Loop: " << lp << " Time elapsed is: " << elapsed[lp] << endl;
    }
    cout << "Average time is: " << accumulate(elapsed, elapsed + 100, 0) / 100 << endl;
}