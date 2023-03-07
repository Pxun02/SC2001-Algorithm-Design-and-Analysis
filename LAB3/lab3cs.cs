using System;

namespace cs {
    public class lab3cs {
        public static void Main(string[] args){
            const int C = 14;
            const int n = 3;
            int P = new int[C+1];

            Console.WriteLine("<< C = 14 and n = 3 >>\n");

            Console.WriteLine("------(1)------\n");
            int w = new int[] {4, 6, 8};
            int p = new int[] {7, 6, 9};
            Console.WriteLine("w | 4 | 6 | 8 |");
            Console.WriteLine("  -------------");
            Console.WriteLine("p | 7 | 6 | 9 |\n");

            for(int i=0;i<n;i++){
                for(int weight=w[i],;weight<=C;weight++){
                    P[weight] = max(P[weight], P[weight - w[i]] + p[i]);
                }
            }

            Console.WriteLine("The result is: ");
            Console.WriteLine(string.Format"{}\n", P[C]); 
        }
    }
}