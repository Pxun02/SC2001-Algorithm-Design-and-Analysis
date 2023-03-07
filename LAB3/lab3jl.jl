C = 14
n = 3
P = [0 for i in 1:C]

println("<< C = 14 and n = 3 >>\n")

println("------(1)------\n")
w = [4, 6, 8]
p = [7, 6, 9]
println("w | 4 | 6 | 8 |")
println("  -------------")
println("p | 7 | 6 | 9 |\n")

for i in 1:n
    for weight in w[i]+1:C
        P[weight] = max(P[weight], P[weight - w[i]] + p[i])
    end
end

println("The result is: ", P[C], "\n")


println("------(2)------\n")
w[1] = 5
println("w | 5 | 6 | 8 |")
println("  -------------")
println("p | 7 | 6 | 9 |\n")

#Initialisation of P
P = [0 for i in 1:C]

for i in 1:n
    for weight in w[i]+1:C
        P[weight] = max(P[weight], P[weight - w[i]] + p[i])
    end
end

println("The result is: ", P[C], "\n")
