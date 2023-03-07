import kotlin.math.*
fun main(args: Array<String>){
    val C = 14
    val n = 3
    var P = IntArray(C+1){0}

    println("<< C = 14 and n = 3 >>\n")

    println("------(1)------\n")
    var w = intArrayOf(4, 6, 8)
    val p = intArrayOf(7, 6, 9)
    println("w | 4 | 6 | 8 |")
    println("  -------------")
    println("p | 7 | 6 | 9 |\n")

    for(i in 0..n-1){
        for(weight in w[i]..C){
            P[weight] = max(P[weight], P[weight - w[i]] + p[i])
        }
    }
    print("The result is: ")
    println(P[C])
    println()
    
    println("------(2)------\n")
    w[0] = 5
    println("w | 5 | 6 | 8 |")
    println("  -------------")
    println("p | 7 | 6 | 9 |\n")
    
    for(i in 0..C)	P[i] = 0

    for(i in 0..n-1){
        for(weight in w[i]..C){
            P[weight] = max(P[weight], P[weight - w[i]] + p[i])
        }
    }
    print("The result is: ")
    println(P[C])
    println()
}