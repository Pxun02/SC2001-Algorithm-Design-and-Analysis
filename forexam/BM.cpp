#include <iostream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
const int n = 10;

void computeJumps(string P, int m, int alpha, map<char, int>& charJump){
    char ch; int k;
    for(ch=0;ch<alpha;ch++)
        charJump[ch] = m;
    for(k=1;k<=m;k++)
        charJump[P[k]] = m - k;
}

int simpleBMScan(string P, string T, int m, map<char, int>& charJump){
    int j = m, k = m;
    while(j<=n){
        if(k<1) return j + 1;
        if(T[j]==P[k]){ j--; k--; }
        else{
            j += max(charJump[T[j]], m - k + 1);
            k = m;
        }
    }
    return -1;
}

int BMScan(string P, string T, int m, map<char, int>& charJump, int matchJump[]){
    int j = m, k = m;
    while(j<=n){
        if(k<1) return j + 1;
        if(T[j]==P[k]){ j--; k--; }
        else{
            j += max(charJump[T[j]], matchJump[k]);
            k = m;
        }
    }
    return -1;
}

int main(){
    string P = "crackers";
    map<char, int> charJump;
    set<char> s;
    for(auto p: P)  s.insert(p);
    computeJumps(P, P.length(), s.size(), charJump);
    for(auto cj: charJump)
        cout << cj.first << " " << cj.second << endl;
}