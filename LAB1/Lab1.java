import java.util.Arrays;
public class Lab1 {

    public static final int K = 5;
    public static void insertionSort(int A[], int p, int q) {
        for (int i = p; i < q; i++) {
            int tempVal = A[i + 1];
            int j = i + 1;
            while (j > p && A[j - 1] > tempVal) {
                A[j] = A[j - 1];
                j--;
            }
            A[j] = tempVal;
        }
        int[] temp = Arrays.copyOfRange(A, p, q +1);
        Arrays.stream(temp).forEach(i -> System.out.print(i + " "));
        System.out.println();
    }

    public static void merge(int A[], int p, int q, int r) {
        int n1 = q - p + 1;
        int n2 = r - q;
        int[] LA = Arrays.copyOfRange(A, p, q +1);
        int[] RA = Arrays.copyOfRange(A, q+1, r +1);
        int RIDX = 0;
        int LIDX = 0;
        for (int i = p; i < r - p + 1; i++) {
            if (RIDX == n2) {
                A[i] = LA[LIDX];
                LIDX++;
            } else if (LIDX == n1) {
                A[i] = RA[RIDX];
                RIDX++;
            } else if (RA[RIDX] > LA[LIDX]) {
                A[i] = LA[LIDX];
                LIDX++;
            } else {
                A[i] = RA[RIDX];
                RIDX++;
            }
        }
    }

    public static void sort(int A[], int p, int r) {
        if (r - p > K) {
            int q = (p + r) / 2;
            sort(A, p, q);
            sort(A, q + 1, r);
            merge(A, p, q, r);
        } else {
            insertionSort(A, p, r);
        }
    }

    public static void main(String string[]) {
        int[] A = { 2, 5, 1, 6, 7, 3, 8, 4, 9 };
        sort(A, 0, A.length - 1);
        Arrays.stream(A).forEach(i -> System.out.print(i + " "));
    }
}
