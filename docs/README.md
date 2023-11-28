# Fibonacci Heap
<div id="badges">
 <img src=https://img.shields.io/badge/CLion-grey?style=for-the-badge&logo=clion&logoColor=white></img>
 <img src=https://img.shields.io/badge/CMake-orange?style=for-the-badge&logo=cmake&logoColor=white></img>
 <img src=https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white></img>
 <img src=https://img.shields.io/badge/c++-black?style=for-the-badge&logo=c%2B%2B&logoColor=white></img>

</div>



## Some information
---
<div>
Fibonacci Heaps were introduced in Fibonacci heaps and their uses in improved network optimization algorithms by Fredman and Tarjan in 1987.

This C++ implementation was based on lectures by ITMO and MIPT teachers such as Pavel Mavrin and Ilya Stepanov.
</div>


##  Usage
---
The Fibonacci Heap is implemented in the FibonacciHeap.hpp header file. It is templated on the type of the elements it stores. The Fibonacci Heap is a min-heap, i.e. the element with the smallest key is always at the top. This implementation supports the following operations:

* `insert(key)`: Inserts a new element with the given key into the heap.
* `merge(other_heap)`: Unites the heap with the given heap. The other heap is empty afterwards.
* `getMin()`: Returns the smallest key in the heap.
* `extractMinimum()`: Returns the smallest key in the heap and removes it from the heap.
* `decreaseKey(element, new_key)`: Decreases the key of the given element to the new key. The new key - must be smaller than the old key.
* `deleteElement(element)`: Deletes the given element from the heap.
* `isEmpty()`: Returns whether the heap is empty.
* `copy(original_heap)`: Сreates a copy of another heap with memory allocation and return root of heap


## Visualization
---
<img src= https://neerc.ifmo.ru/wiki/images/f/f3/Fibonacci-heap.png>
