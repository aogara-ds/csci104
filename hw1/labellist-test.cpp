#include <iostream>
#include "labellist.h"
using namespace std;

int main()
{
    LabelList l1;
    l1.add("Hello");
    l1.add("Bye");
    l1.print(std::cout, "all", ' ');
    return 0;
}