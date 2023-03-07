#include <iostream>
#include <vector>
using namespace std;

const int C = 14;
const int n = 3;
int P[C+1];

int main(){
    cout << "<< C = 14 and n = 3 >>\n" << endl;

    cout << "------(1)------\n" << endl;
    int w[n] = {4, 6, 8};
    int p[n] = {7, 6, 9};
    cout << "w | "; 
    for(int _w: w) cout << _w << " | ";
    cout << endl;
    cout << "  -------------" << endl;
    cout << "p | ";
    for(int _p: p) cout << _p << " | ";
    cout << "\n" << endl;
    
    for(int i=0;i<=C;i++) P[i] = 0;

    for(int i=0;i<n;i++){
        for(int weight=w[i];weight<=C;weight++){
            P[weight] = max(P[weight], P[weight - w[i]] + p[i]);
        }
    }

    cout << "The result is: ";
    cout << P[C] << "\n" << endl;    

    cout << "------(2)------\n" << endl;
    w[0] = 5;
    cout << "w | "; 
    for(int _w: w) cout << _w << " | ";
    cout << endl;
    cout << "  -------------" << endl;
    cout << "p | ";
    for(int _p: p) cout << _p << " | ";
    cout << "\n" << endl;
    
    for(int i=0;i<=C;i++) P[i] = 0;

    for(int i=0;i<n;i++){
        for(int weight=w[i];weight<=C;weight++){
            P[weight] = max(P[weight], P[weight - w[i]] + p[i]);
        }
    }

    cout << "The result is: ";
    cout << P[C] << endl;
}
