object lab3sc{
    def main(args: Array[String]): Unit = {
        val C = 14
        val n = 3
        var P = new Array[Int](C+1)

        println("<< C = 14 and n = 3 >>\n")

        println("------(1)------\n")
        var w = List(4, 6, 8)
        val p = List(7, 6, 9)
        println("w | 4 | 6 | 8 |")
        println("  -------------")
        println("p | 7 | 6 | 9 |\n")

        for(i <- 0 until n){
            for(weight <- w(i) to C){
                P(weight) = P(weight).max(P(weight - w(i)) + p(i))
            }
        }

        print("The result is: ")
        println(P(C) + "\n")
        
        println("------(2)------\n")
        w = 5 :: w.takeWhile(_ > 0)
        println("w | 5 | 6 | 8 |")
        println("  -------------")
        println("p | 7 | 6 | 9 |\n")
        
        for(i <- 0 to C){
            P(i) = 0
        }

        for(i <- 0 until n){
            for(weight <- w(i) to C){
                P(weight) = P(weight).max(P(weight - w(i)) + p(i))
            }
        }

        print("The result is: ")
        println(P(C))
    }
}
