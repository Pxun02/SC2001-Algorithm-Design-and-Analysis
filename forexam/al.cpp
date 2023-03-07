#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string S1 = "ctatg";
string S2 = "ttaagc";

int alignment(int n1, int n2){
    S1 = "0" + S1; S2 = "0" + S2;
    int dp[n1+1][n2+1];
    for(int i=0;i<=n1;i++){
        for(int j=0;j<=n2;j++){
            if(i==0)    dp[i][j] = j;
            else if(j==0)   dp[i][j] = i;
            else if(S1[i]==S2[j])   dp[i][j] = dp[i-1][j-1];
            else{
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1;
            }
        }
    }
    return dp[n1][n2];
}

int main(){
    cout << alignment(S1.length(), S2.length()) << endl;
}