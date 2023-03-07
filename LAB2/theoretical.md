<script type="text/javascript"  async　src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.7/MathJax.js?config=TeX-MML-AM_CHTML">  </script>  <script type="text/x-mathjax-config"> MathJax.Hub.Config({ tex2jax: { inlineMath: [['$', '$'] ], displayMath: [ ['$$','$$'], ["\\[","\\]"] ] } }); 
</script>

# SC2001 Lab2 Dijkstra

## Average Complexity of Dijkstra's algorithm with Adj List & Heap Priority Queue
### Length of sequence of possible |E|:
$$\begin{aligned}
\begin{split}
 (SequenceLength) &=  \binom{|V|}{2} - (|V| - 1) + 1 \\[5mm]
 &= \frac{|V| ^ {2} - |V|}{2} - |V| + 2 \\[5mm]
 &= \frac{1}{2}(|V|^{2} - 3|V| + 4) \\[5mm]
 &\equiv n.
 \end{split}
 \end{aligned}$$

### Sum of all possible scenarios:
$$\begin{aligned}
\begin{split}
 \displaystyle\sum_{|E| = |V| - 1} ^ \frac{|V| ^ {2} - |V|}{2} (|E| + |V| ) \log(|V|)
&= \biggl\{ \left( \frac{|V| ^ {2} - |V|}{2} + |V| - 1 \right) \cdot n \cdot \frac{1}{2} + n \cdot |V| \biggr\} \cdot \log(|V|) \\[5mm]
&= \frac{n}{4} \cdot (|V| ^ {2} - |V| + 2|V| - 2 + 4|V|) \cdot \log(|V|) \\[5mm]
&= \frac{n}{4} \cdot (|V| ^ {2} +5|V| - 2) \cdot \log(|V|) \\[5mm]
&\equiv S.  
\end{split}
 \end{aligned}$$

### Thus, Average Complexity is:
$$
\frac{S}{n} = \frac{1}{4} \cdot (|V| ^ {2} + 5|V| - 2) \cdot \log(|V|) \in O(|V| ^ {2} \log(|V|)).
$$

## Fixed |E| with varying |V|
### As the range of |E| is:
$$|V| - 1 \leq |E| \leq \frac{|V| ^ {2} - |V|}{2},$$

### we derive:
$$
|V| \leq |E| + 1, |V| ^{2} - |V| - 2|E| \geq 0. \\[5mm]
|V| \leq |E| + 1, |V| \leq \frac{1-\sqrt{1+8|E|}}{2}, \frac{1+\sqrt{1+8|E|}}{2} \leq |V|.
$$

 ### As |E| >= 1,
 $$
obtains \quad |E| + 1 \geq \frac{1+\sqrt{1+8|E|}}{2},\quad and \\[5mm]
\frac{1+\sqrt{1+8|E|}}{2} \leq |V| \leq |E| + 1. \\
$$
 &emsp; for Adj Matrix & Array:
$$\frac{1 + 4|E| + \sqrt{1 + 8|E|}}{2} \leq |V| ^ {2} \leq (|E| + 1) ^ {2}, \\[2mm]
Best Case:O(|E|), \\[2mm]
WorstCase: O(|E|^ {2} ).$$
&emsp;  for Adj List & Heap:
$$
\left( |E| + \frac{1 + \sqrt{1 + 8|E|}}{2} \right) \log{ \left( \frac{1 + \sqrt{1 + 8|E|}}{2} \right) } \\[5mm] \leq (|E| + |V|) \log{(|V|)} \\[5mm]
 \leq (2|E| + 1) \log(|E| + 1), \\[5mm]
 BestCase: O(|E| \log{(|E|)}) \\[2mm]
 WorstCase: O(|E| \log{(|E|)})
 $$

### Therefore, when the value of |V| is relatively small, Adj Matrix & Array is faster than Adj List & Heap; whereas when the value of |V| is relatively large, Adj List&Heap is faster.

## Fixed |V| with varying |E|
### The range of |E| is:
$$ |V| - 1 \leq |E| \leq \frac{|V| ^ {2} - |V|}{2}.$$

&emsp; for Adj Matrix & Array:
$$O(|V|^{2}).$$
&emsp; (This is not so much affected by |E|)

&emsp; for Adj List & Heap:
$$(2|V| - 1) \log{(|V|)} \leq (|E| + |V|) \log{(|V|)} \leq 
\frac{|V|^{2} + |V|}{2} \log{(|V|)}. \\[5mm]
BestCase: O(|V| \log{(|V|)}) \\[2mm]
WorstCase: O(|V| ^ {2} \log{(|V|)})$$

### Therefore, when the value of |E| is relatively small, Adj List & Heap is faster than Adj Matrix & Array; whereas when the value of |E| is relatively large, Adj Matrix & Array is faster.
than Adj List & Heap. 