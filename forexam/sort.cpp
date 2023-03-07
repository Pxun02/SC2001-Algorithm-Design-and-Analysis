#include <iostream>
using namespace std;

int slot[10] = {77,15,96,89,42,80,35,4,93,6};

//merge sort
int compare(int a, int b){
    if(a>b) return 1;
    else if(a==b)   return 0;
    else    return -1;
}

void merge(int n, int m){
    int mid = (n+m)/2;
    int a = n, b = mid+1, i, cmp, tmp;
    if(m-n<=0)  return;
    while(a<=mid && b <= m){
        cmp = compare(slot[a], slot[b]);
        if(cmp>0){
            tmp = slot[b++];
            for(i=++mid;i>a;i--)
                slot[i] = slot[i-1];
            slot[a++] = tmp;
        } else if(cmp<0)
            a++;
        else{
            if(a==mid && b==m)
                break;
            tmp = slot[b++];
            a++;
            for(i=++mid;i>a;i--)
                slot[i] = slot[i-1];
            slot[a++] = tmp;
        }
    }
}

void mergesort(int n, int m){
    int mid = (n+m)/2;
    if(m-n<=0)  return;
    else if(m-n>1){
        mergesort(n, mid);
        mergesort(mid+1, m);
    }
    merge(n, m);
}

//quicksort

int partition(int low, int high){
    int i, last_small, pivot;
    int mid = (low+high)/2;
    swap(slot[low], slot[mid]);
    pivot = slot[low];
    last_small = low;

    for(i=low+1;i<=high;i++){
        if(slot[i]<pivot)
            swap(slot[++last_small], slot[i]);
    }
    swap(slot[low], slot[last_small]);
    return last_small;
}

void quicksort(int n, int m){
    int pivot_pos;
    if(n>=m)    return;
    pivot_pos = partition(n, m);
    quicksort(n, pivot_pos-1);
    quicksort(pivot_pos+1, m);
}

int main(){
    quicksort(0, 9);
    for(int i=0;i<10;i++)    cout << slot[i] << " ";
    cout << endl;
}
