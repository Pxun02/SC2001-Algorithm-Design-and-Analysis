#include <iostream>
#include <algorithm>
using namespace std;

int w[5] = {0,4,6,8,6};
int p[5] = {0,7,6,9,5};

int knapsack(int w[], int p[], int C, int n){
    int profit[C+1][n+1];
    for(int c=0;c<=n;c++)   profit[0][c] = 0;
    for(int r=1;r<=C;r++)   profit[r][0] = 0;
    for(int r=1;r<=C;r++){
        for(int c=1;c<=n;c++){
            if(w[c]>r)
                profit[r][c] = profit[r][c-1];
            else
            profit[r][c] = max(profit[r][c-1], profit[r-w[c]][c-1] + p[c]);
        }
    }
    for(int i=0;i<=C;i++){
        for(int j=0;j<=n;j++){
            cout << profit[i][j];
            if(j!=n)    cout << "\t";
            else    cout << endl;
        }
    }
    return profit[C][n];
}

int main(){
    int pf = knapsack(w, p, 20, 4);
}