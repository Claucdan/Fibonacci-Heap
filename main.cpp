#include <iostream>
#include <vector>
#include <string>
#include "Fibonacciheap.h"
//Hello
int main(){
    FibonacciHeap fibonacciHeap1;
    fibonacciHeap1.insert(213);
    fibonacciHeap1.insert(123);
    fibonacciHeap1.insert(154);

    FibonacciHeap fibonacciHeap2;
    fibonacciHeap2.insert(143);
    fibonacciHeap2.insert(177);
    fibonacciHeap2.insert(255);

    std::cout<<"Extract from first heap: "<<fibonacciHeap1.getMinimum()<<"\n"<<"\n";
    fibonacciHeap1.removeMinimum();

    FibonacciHeap fibonacciHeap3(fibonacciHeap1,fibonacciHeap2);

    std::cout<<"Extract from third heap: "<<fibonacciHeap3.getMinimum()<<"\n";
    fibonacciHeap3.removeMinimum();
    std::cout<<"Extract from third heap: "<<fibonacciHeap3.getMinimum()<<"\n";
    fibonacciHeap3.removeMinimum();
    std::cout<<"Extract from third heap: "<<fibonacciHeap3.getMinimum()<<"\n"<<"\n";
    fibonacciHeap3.removeMinimum();

    std::cout<<"Extract from first heap: "<<fibonacciHeap1.getMinimum()<<"\n"<<"\n";
    fibonacciHeap1.removeMinimum();

    std::cout<<"Extract from second heap: "<<fibonacciHeap2.getMinimum()<<"\n";
    fibonacciHeap2.removeMinimum();



    return 0;
}