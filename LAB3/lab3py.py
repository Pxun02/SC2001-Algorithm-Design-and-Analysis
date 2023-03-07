C = 14
n = 3
P = [0 for i in range(C+1)]

print("<< C = 14 and n = 3 >>\n")

print("------(1)------\n")
w = [4, 6, 8]
p = [7, 6, 9]
print("w | 4 | 6 | 8 |")
print("  -------------")
print("p | 7 | 6 | 9 |\n")

for i in range(n):
    for weight in range(w[i], C+1):
        P[weight] = max(P[weight], P[weight - w[i]] + p[i])

print(f"The result is: {P[C]}\n")


print("------(2)------\n")
w[0] = 5
print("w | 5 | 6 | 8 |")
print("  -------------")
print("p | 7 | 6 | 9 |\n")

#initialisaton of P
P = [0 for i in range(C+1)]

for i in range(n):
    for weight in range(w[i], C+1):
        P[weight] = max(P[weight], P[weight - w[i]] + p[i])

print(f"The result is: {P[C]}\n")
