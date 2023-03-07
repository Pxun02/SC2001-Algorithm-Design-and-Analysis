public class lab3jv {
    public static void main(String[] args){
        final int C = 14;
        final int n = 3;
        int P[] = new int[C+1];

        System.out.println("<< C = 14 and n = 3 >>\n");

        System.out.println("------(1)------\n");
        int w[] = {4, 6, 8};
        int p[] = {7, 6, 9};
        System.out.println("w | 4 | 6 | 8 |");
        System.out.println("  -------------");
        System.out.println("p | 7 | 6 | 9 |\n");
        
        //Initialisation of P
        for(int i=0;i<=C;i++) P[i] = 0;

        for(int i=0;i<n;i++){
            for(int weight=w[i];weight<=C;weight++){
                P[weight] = P[weight] > P[weight - w[i]] + p[i] ? P[weight] : P[weight - w[i]] + p[i];
            }
        }

        System.out.print("The result is: ");
        System.out.println(P[C] + "\n");  
        

        System.out.println("------(2)------\n");
        w[0] = 5;        
        System.out.println("w | 5 | 6 | 8 |");
        System.out.println("  -------------");
        System.out.println("p | 7 | 6 | 9 |\n");
        
        //Initialisation of P
        for(int i=0;i<=C;i++) P[i] = 0;

        for(int i=0;i<n;i++){
            for(int weight=w[i];weight<=C;weight++){
                P[weight] = P[weight] > P[weight - w[i]] + p[i] ? P[weight] : P[weight - w[i]] + p[i];
            }
        }

        System.out.print("The result is: ");
        System.out.println(P[C] + "\n");    
    }
}
    