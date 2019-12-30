# Huffman Coding

<p>
  <img src="https://img.shields.io/pypi/status/Django.svg"/>
  <img src="https://img.shields.io/badge/contributions-welcome-orange.svg"/>
</p>

<a href="https://en.wikipedia.org/wiki/Huffman_coding">Huffman code</a> is a particular type of optimal prefix code that is commonly used for lossless data compression. The process of finding or using such a code proceeds by means of Huffman coding, an algorithm developed by David A. Huffman.

## Objective
Huffman’s algorithm takes a very simple idea and finds an elegant way to implement it. At its heart is the observation that the more a thing is mentioned, the shorter its name should be. This idea manifests itself in daily life too. For example, we use nicknames for people we call often, we have abbreviations for long words we often have to use and even the word ok was once an abbreviation for “all correct”.

Translated to the world of computers, it means that if a chunk of data repeats itself more than another chunk of data in the same group, it is best to encode the more occurring chunk with smaller code word. Practically what it means is that the compressed file has two parts:
* Dictionary of code words and their corresponding chunks of data. 
* The data itself, encoded using codewords
  <p><b><i>i.e.</i></b> often called payload in compression jargon.</p>
</br>
During decompression, the dictionary is read and the codewords are sequentially translated into actual data.

Say this is the data you want to compress:
``` 
BANANA
```

The ASCII codes for the alphabets in binary are:
```
B : 01000010
A : 01000001
N : 01001110
```

Thus the ASCII encoding of BANANA is:
```
01000010 01000001 01001110 
01000001 01001110 01000001
```

Let’s try to compress this with the aforementioned scheme of calling more frequent chunks of data with smaller nicknames. We will start with a naive interpretation.
```
A : Occurs thrice. Let’s call it a 0
N : Occurs twice. Let’s call it a 1
B : Occurs once. Let’s call it a 10
```

The compressed data thus turns out to be:
```
1001010
```

</br>

## Pseudocode
### Compression
```
// C is the set of n
Procedure Huffman(C):     
characters and related information
n = C.size
Q = priority_queue()
for i = 1 to n
    n = node(C[i])
    Q.push(n)
end for
while Q.size() is not equal to 1
    Z = new node()
    Z.left = x = Q.pop
    Z.right = y = Q.pop
    Z.frequency = x.frequency + y.frequency
    Q.push(Z)
end while
Return Q
```

### Decompression
```
// root represents the root of Huffman Tree
Procedure HuffmanDecompression(root, S):   

// S refers to bit-stream to be decompressed
n := S.length                              
for i := 1 to n
    current = root
    while current.left != NULL and current.right != NULL
        if S[i] is equal to '0'
            current := current.left
        else
            current := current.right
        endif
        i := i+1
    endwhile
    print current.symbol
endfor
```

</br>

## Data Structures Used
* Heap-Nodes 
* Heaps / Priority Queues and their associated heap nodes 
* Huffman Trees 
* Hash-Maps
* Frequency Hash-Map
* Character Code Hash-Map

</br>

## Complexities
* O(n*lg(n)) for building Huffman Trees
* O(lg(n)) for each individual heapify operation 
* O(n*f(c)) for encoding each Character and writing it to file 
  * n is the number Of characters 
  * f(c) is the frequency of that character.
* O(1) for value retrieval of each key in the Hash-Map 
* O(n) for decompression of a single file 
  * n is the number of bytes in that file. 
  
<p><b><i>i.e.</i></b> This can be generalized to O(N*n(i))</p>

* n is the number of files required to be decompressed.
* n(i) is the number of bytes in file i.
</br>

## Usage
Terminal based program.
```
Usage:
	./Huffman <mode> -i <input-file> -o <output-file>
	./Huffman <mode> -m -i <input-folder>
	./Huffman <mode> <option> -i <input-file> -o <output-file>

Modes:
	-c		Compresses input file.
	-d		Decompresses input file.

Options:
	-v		Verbose mode.
	-m		Multiple mode.
```
