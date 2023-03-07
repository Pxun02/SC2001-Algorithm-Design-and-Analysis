#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <iterator>
#include <numeric>
#include <string>
#include <random>
#include <cstring>

using namespace std;

int compare(int x, int y){
    int ans = x - y;
    if(ans>0)   return 1;
    if(ans==0)  return 0;
    return -1;
}

void generate_arrays(int high, int* arrays, int size){
    for (int i = 0; i < size; i++) {
		arrays[i] = rand() % high + 1;
	}
}

namespace mySorts {
    class HybridSort {
        public:
            HybridSort(){}
            ~HybridSort(){}
        
            void merge(int* array, int n, int m){
                int mid = (n + m) / 2;
                int a = n, b = mid + 1, i, tmp;
                if(m - n <= 0)  return;
                while(a <= mid && b <= m){
                    int cmp = compare(array[a], array[b]);
                    if(cmp > 0){
                        tmp = array[b++];
                        for(int i = ++mid; i > a; i--)
                            array[i] = array[i - 1];
                        array[a++] = tmp;
                    } else if(cmp < 0)
                        a++;
                    else {
                        if(a == mid && b == m)
                            break;
                        tmp = array[b++];
                        a++;
                        for(int i = ++mid; i > a; i--)
                            array[i] = array[i - 1];
                        array[a++] = tmp;
                    }
                }
            }

            void hybrid_sort(int* array, int S, int n, int m){
                if(n <= S){
                    for(int i = 1; i < S; i++){
                        for(int j = i; j > 0; j --){
                            if(array[j] < array[j - 1])
                                swap(array[j], array[j - 1]);
                            else    break;
                        }
                    }
                }else{
                    int mid = (n + m) / 2;
                    if(m - n <= 0)
                        return;
                    else if(m - n > 1){
                        hybrid_sort(array, S, n, mid);
                        hybrid_sort(array, S, mid + 1, m);
                    }
                    merge(array, n, m);
                }
            }

    };
    class HybridSortUtility: public HybridSort{
        public:
            int key_comparisons_S[10000001];
            int key_comparisons_n[1001];
            HybridSortUtility(){
                memset(&key_comparisons_S, 0, 10000001);
                memset(&key_comparisons_n, 0, 1001);
            }
            ~HybridSortUtility(){}
            void hybrid_sort(int* array, int S, int n, int m, int x){
                if(m - n + 1 <= S){
                    for(int i = n; i <= m; i++){
                        for(int j = i; j > n; j--){
                            //this->key_comparisons_S[x]++;
                            //this->key_comparisons_n[S]++;
                            if(array[j] < array[j - 1])
                                swap(array[j], array[j - 1]);
                            else    break;
                        }
                    }
                }else{
                    int mid = (n + m) / 2;
                    if(m - n <= 0)
                        return;
                    else if(m - n > 1){
                        hybrid_sort(array, S, n, mid, x);
                        hybrid_sort(array, S, mid + 1, m, x);
                    }
                    merge(array, n, m, x, S);
                }
            }

            void merge(int* array, int n, int m, int x, int S){
                int mid = (n + m) / 2;
                int a = n, b = mid + 1, i, tmp;
                if(m - n <= 0)  return;
                while(a <= mid && b <= m){
                    int cmp = compare(array[a], array[b]);
                    //this->key_comparisons_S[x]++;
                    //this->key_comparisons_n[S]++;
                    if(cmp > 0){
                        tmp = array[b++];
                        for(int i = ++mid; i > a; i--)
                            array[i] = array[i - 1];
                        array[a++] = tmp;
                    } else if(cmp < 0)
                        a++;
                    else {
                        if(a == mid && b == m)
                            break;
                        tmp = array[b++];
                        a++;
                        for(int i = ++mid; i > a; i--)
                            array[i] = array[i - 1];
                        array[a++] = tmp;
                    }
                }
            }
    };

    class OriginalMergeSort: public HybridSort{
        public:
            int key_comparisons_n;
            OriginalMergeSort(){
                key_comparisons_n = 0;
            }
            ~OriginalMergeSort(){}
 
            void mergeSort(int* array, int n, int m){
                int mid = (n + m) / 2;
                if(m - n <= 0)
                    return;
                else if(m - n > 1){
                    mergeSort(array, n, mid);
                    mergeSort(array, mid + 1, m);
                }
                merge(array, n, m);
            }

            void merge(int* array, int n, int m){
                int mid = (n + m) / 2;
                int a = n, b = mid + 1, i, tmp;
                if(m - n <= 0)  return;
                while(a <= mid && b <= m){
                    int cmp = compare(array[a], array[b]);
                    //this->key_comparisons_n++;
                    if(cmp > 0){
                        tmp = array[b++];
                        for(int i = ++mid; i > a; i--)
                            array[i] = array[i - 1];
                        array[a++] = tmp;
                    } else if(cmp < 0)
                        a++;
                    else {
                        if(a == mid && b == m)
                            break;
                        tmp = array[b++];
                        a++;
                        for(int i = ++mid; i > a; i--)
                            array[i] = array[i - 1];
                        array[a++] = tmp;
                    }
                }
            }
    };
}

using namespace mySorts;

int main(){
    cout << "Input the size of datasets: ";
    int x; cin >> x;
    int* array = new int[x];
    for (int i = 0; i < x; i++) {
		array[i] = rand() % x + 1;
	}

    //Analyze time complexity.
    cout << "Input an integer S as a threshold for the size of subarray: ";
    int S; cin >> S;
    

        HybridSortUtility *hsu = new HybridSortUtility();
        int arrays[x];
        copy(array, array+x, arrays);
        chrono::system_clock::time_point start, end;
        start = chrono::system_clock::now();
        hsu->hybrid_sort(arrays, S, 0, x-1, x);
        end = chrono::system_clock::now();
        double elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();
        //cout << "S: " << S << ", comparisons: " << hsu->key_comparisons_S[x] << endl;
        cout << "S: " << S << ", CPU times: " << elapsed << endl;
    
    
    /*
    HybridSortUtility *hsu = new HybridSortUtility();
    chrono::system_clock::time_point start, end;
    start = chrono::system_clock::now();
    hsu->hybrid_sort(array, S, 0, x-1, x);
    end = chrono::system_clock::now();
    double elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    //cout << "S: " << S << ", comparisons: " << hsu->key_comparisons_S[x] << endl;
    cout << "size: " << x << ", CPU times: " << elapsed << endl;
    */
    
    
    /*
    HybridSortUtility *hsu = new HybridSortUtility();
    hsu->hybrid_sort(array, S, 0, x - 1, x);
    cout << "comparisons: " << hsu->key_comparisons_n[S] << endl;
    */

   /*
    for(int i = 0; i < 10; i++){
        HybridSortUtility *hsu = new HybridSortUtility();
        hsu->hybrid_sort(array, S, 0, x - 1, x);
        cout << "n: " << i << ", comparisons: " << hsu->key_comparisons_n[S] << endl;
    }
    */
    
   /*
    for(int j=0;j<10;j++){
        int* array = new int[x];
        for (int i = 0; i < x; i++) {
            array[i] = rand() % x + 1;
        }
        OriginalMergeSort* oms = new OriginalMergeSort();
        chrono::system_clock::time_point start, end;
        start = chrono::system_clock::now();

        oms->mergeSort(array, 0, x - 1);

        end = chrono::system_clock::now();
        double elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();
        cout << "CPU time is: " << elapsed <<  "ms" << endl;
   }
   */
   /*
    OriginalMergeSort* oms = new OriginalMergeSort();

    chrono::system_clock::time_point start, end;
    start = chrono::system_clock::now();

    oms->mergeSort(array, 0, x - 1);

    end = chrono::system_clock::now();
    double elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    
    //cout << "n: " << x << ", comparisons: " << oms->key_comparisons_n << endl;
    cout << "size: " << x <<  "\nRuntime using merge sort: " << elapsed <<  "ms" << endl;
    */
    /*
    //(d)
    cout << "Optimal value of S obtained in (c) is: ";
    cin >> S;
    OriginalMergeSort* oms = new OriginalMergeSort();

    chrono::system_clock::time_point start, end;
    start = chrono::system_clock::now();

    oms->merge(arrays, 0, S);

    end = chrono::system_clock::now();
    double elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    
    cout << "The number of key comparisons is: " << oms->key_comparisons_S << endl;
    cout << "CPU time is: " << elapsed <<  "ms" << endl;
    */
}