#include <iostream>
#include <algorithm>

using namespace std;

int d[5] = {30, 1, 40, 10, 25};
int cost[5][5];
int last[5][5];

void matrixOrder(int d[], int n){
    for(int i=0;i<n;i++)    cost[i][i+1] = 0;
    for(int l=2;l<=n;l++){
        for(int i=0;i<=n-l;i++){
            int j = i + l;
            cost[i][j] = INT_MAX;
            for(int k=i+1;k<j;k++){
                int c = cost[i][k] + cost[k][j] + d[i] * d[k] * d[j];
                if(c<cost[i][j]){
                    cost[i][j] = c;
                    last[i][j] = k;
                }
            }
        }
    }
}

int main(){
    matrixOrder(d,4);
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout << cost[i][j];
            if(j!=4)    cout << "\t";
            else cout << endl;
        }
    }
    cout << endl;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout << last[i][j];
            if(j!=4)    cout << "\t";
            else cout << endl;
        }
    }
}