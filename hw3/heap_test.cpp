#include <iostream>
#include "heap.h"
using namespace std;

int main()
{
    // TODO: Choose your own template arguments
    // Requires a valid PComparator

    // ObjAComparator c1( /* some constructor arguments as desired */ );
    // Heap<ObjA, ObjAComparator> h1(2, c1);
    
    Heap<> h;

    // TODO: Build a 3-ary heap


    std::cout << "Size: " << h.size() << std::endl;
    std::cout << "Empty: " << h.empty() << std::endl;
    // std::cout << "Top: " << h.top() << std::endl;
    
    h.push(10);
    h.push(5);
    h.push(20);
    std::cout << "Expect 5, Top: " << h.top() << std::endl;

    h.push(2);
    h.push(8);
    std::cout << "Expect 2, Top: " << h.top() << std::endl;

    h.pop();
    std::cout << "Expect 4, Size: " << h.size() << std::endl;
    std::cout << "Expect 5, Top: " << h.top() << std::endl;


    h.pop();
    std::cout << "Expect 3, Size: " << h.size() << std::endl;
    std::cout << "Expect 8, Top: " << h.top() << std::endl;

    h.push(12);
    h.push(20);
    h.push(1);
    h.push(3);
    std::cout << "Expect 1, Top: " << h.top() << std::endl;

    h.pop();
    std::cout << "Expect 3, Top: " << h.top() << std::endl;






    // 3-ary Heap Test




    // 5-ary Heap Test

}

