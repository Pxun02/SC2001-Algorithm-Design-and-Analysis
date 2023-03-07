#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

int c[6][5];
char h[6][5];
string x = " ACGGA";
string y = " ACTG";

int LCS(int n, int m){
    for(int i=0;i<=n;i++)    {c[i][0] = 0; h[i][0] = '|';}
    for(int j=1;j<=m;j++)    {c[0][j]= 0; h[0][j] = '-';}
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(x[i]==y[j]){
                c[i][j] = c[i-1][j-1] + 1;
                h[i][j] = '\\';
            }
            else if(c[i-1][j]>=c[i][j-1]){
                c[i][j] = c[i-1][j];
                h[i][j] = '|';
            }
            else{
                c[i][j] = c[i][j-1];
                h[i][j] = '-';
            }
        }
    }
    return c[n][m];
}

string getSequence(int n, int m){
    stack<char> s;
    int i = n, j = m;
    while(i!=0 && j!=0){
        if(h[i][j]=='\\'){
            s.push(x[i]); i--; j--;
        }
        else if(h[i][j]=='|')
            i--;
        else    j--;
    }

    string ans;
    while(!s.empty()){
        ans.push_back(s.top());
        s.pop();
    }
    return ans;
}

int main(){
    int a = LCS(5, 4);
    cout << a << endl;
    cout << getSequence(5, 4) << endl;
}