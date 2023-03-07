#include <stdio.h>

const int C = 14;
const int n = 3;
int P[C+1];

int main(){
    printf("<< C = 14 and n = 3 >>\n\n");

    printf("------(1)------\n\n");
    int w[n] = {4, 6, 8};
    int p[n] = {7, 6, 9};
    printf("w | 4 | 6 | 8 |\n");
    printf("  -------------\n");
    printf("p | 7 | 6 | 9 |\n\n");
    
    //Initialisation of P
    for(int i=0;i<=C;i++) P[i] = 0;

    for(int i=0;i<n;i++){
        for(int weight=w[i];weight<=C;weight++){
            P[weight] = P[weight] > P[weight - w[i]] + p[i] ? P[weight] : P[weight - w[i]] + p[i];
        }
    }

    printf("The result is: ");
    printf("%d\n\n", P[C]);    

    printf("------(2)------\n\n");
    w[0] = 5;
    printf("w | 5 | 6 | 8 |\n");
    printf("  -------------\n");
    printf("p | 7 | 6 | 9 |\n\n");
    
    //Initialisation of P
    for(int i=0;i<=C;i++) P[i] = 0;

    for(int i=0;i<n;i++){
        for(int weight=w[i];weight<=C;weight++){
            P[weight] = P[weight] > P[weight - w[i]] + p[i] ? P[weight] : P[weight - w[i]] + p[i];
        }
    }

    printf("The result is: ");
    printf("%d\n\n", P[C]);     
}
