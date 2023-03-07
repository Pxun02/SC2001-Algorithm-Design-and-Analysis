#include <iostream>
#include <vector>
using namespace std;

const int C = 14;
const int n = 3;
int P[C+1];
int w[n] = {4, 6, 8};
int p[n] = {7, 6, 9};

int dp(int weight, int i){
    return max(dp(i+1, weight), dp(i+1, weight-w[i])+ p[i]); 
}

int main(){
    cout << "<< C = 14 and n = 3 >>\n" << endl;

    cout << "------(1)------\n" << endl;
    cout << "w | "; 
    for(int _w: w) cout << _w << " | ";
    cout << endl;
    cout << "  -------------" << endl;
    cout << "p | ";
    for(int _p: p) cout << _p << " | ";
    cout << "\n" << endl;
    
    for(int i=0;i<=C;i++) P[i] = 0;

    int ans = 0;
    for(int i=0;i<n;i++){
        for(int weight=C;weight>=w[i];weight--)
            ans = dp(weight, i);
    }
    cout << "The result is: " << ans;
}