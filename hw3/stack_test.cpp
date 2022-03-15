#include <iostream>
#include "stack.h"
using namespace std;

int main()
{
    Stack<int> s;
    std::cout << "Size: " << s.size() << std::endl;
    std::cout << "Empty: " << s.empty() << std::endl;
    // std::cout << "Top: " << s.top() << std::endl;
    
    std::cout << "Pushing..." << std::endl;
    s.push(1);
    s.push(2);
    s.push(3);
    std::cout << "Size: " << s.size() << std::endl;
    std::cout << "Empty: " << s.empty() << std::endl;
    std::cout << "Top: " << s.top() << std::endl;

    std::cout << "Popping..." << std::endl;
    s.pop();
    std::cout << "Size: " << s.size() << std::endl;
    std::cout << "Top: " << s.top() << std::endl;
}

