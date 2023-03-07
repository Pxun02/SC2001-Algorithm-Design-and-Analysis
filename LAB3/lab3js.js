const C = 14
const n = 3;
let P = Array(C+1)

console.log("<< C = 14 and n = 3 >>\n")

console.log("------(1)------\n")
let w = [4, 6, 8]
const p = [7, 6, 9]
console.log("w | 4 | 6 | 8 |")
console.log("  -------------")
console.log("p | 7 | 6 | 9 |\n")

P.fill(0)

for(let i=0;i<n;i++){
    for(let weight=w[i];weight<=C;weight++){
        P[weight] = P[weight] > P[weight - w[i]] + p[i] ? P[weight] : P[weight - w[i]] + p[i]
    }
}

console.log("The result is: %d\n", P[C])

console.log("------(2)------\n")
w[0] = 5
console.log("w | 5 | 6 | 8 |")
console.log("  -------------")
console.log("p | 7 | 6 | 9 |\n")

P.fill(0)

for(let i=0;i<n;i++){
    for(let weight=w[i];weight<=C;weight++){
        P[weight] = P[weight] > P[weight - w[i]] + p[i] ? P[weight] : P[weight - w[i]] + p[i]
    }
}

console.log("The result is: %d\n", P[C])
