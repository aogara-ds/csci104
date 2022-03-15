#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T = int, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

  /**
   * @brief Returns the size of the heap
   * 
   */
  size_t size() const;

  bool blue(int a, int b);


private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int m;
  PComparator compare;

};

// Add implementation of member functions here


// Heap()
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
{
  std::cout << "Heap()" << std::endl;
  Heap::m = m;
}

// ~Heap()
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
  std::cout << "~Heap()" << std::endl;
  // TODO: Do I have to deallocate anything by hand?
  // The data vector and m int are automatically deallocated. 
}

// size()
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return Heap<T,PComparator>::data.size();
}

// empty()
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return (Heap<T,PComparator>::size() == 0);
}

// top()
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  if(empty()){
    throw std::underflow_error("Cannot get top() of empty heap.");
  }

  return Heap<T,PComparator>::data.at(0);
}


// push()
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  // Print statment
  std::cout << "push(" << item << ")" << std::endl;

  // 1. Insert item to end of vector
  Heap<T,PComparator>::data.push_back(item);

  // 2. Trickle up
  // Implementation borrowing directly from Lab 6
  std::size_t index = Heap<T,PComparator>::size() - 1;
  while (index != 0) {
      std::size_t parent_index = (index - 1) / Heap::m;
      T& current = data[index];
      T& parent = data[parent_index];
      if (compare(parent, current)) {
          break;
      }
      std::cout << "trickling up" << std::endl;
      std::swap(current, parent);
      index = parent_index;
  }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::blue(int a, int b)
{
  return PComparator(a, b);
}


// pop()
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  // Print statment
  std::cout << "pop()" << std::endl;
  std::cout << "best element: " << Heap<T,PComparator>::data.at(0) << std::endl;
  
  // Make sure the heap isn't empty
  if(empty()){
    throw std::underflow_error("Cannot get top() of empty heap.");
  }

  // Swap first and last
  std::cout << "swapped" << std::endl;
  size_t last_idx = Heap<T,PComparator>::size() - 1;
  std::swap(Heap<T,PComparator>::data.at(0), Heap<T,PComparator>::data.at(last_idx));

  // Erase last
  std::cout << "erased" << std::endl;
  Heap<T,PComparator>::data.pop_back();

  // What are indexes
  //         0
  //    1          2
  //  3   4     5     6 
  // 7 8 9 10 11 12 13 14

  //         1
  //    2          3
  //  4   5     6     7 
  // 8 9 

  // 3-ary Heap
  //                    1
  //       2            3           4
  //   5   6   7    8   9  10   11  12  13

  //                    0
  //       1            2            3
  //   4   5   6    7   8   9    10  11  12

  // 3n+1, 2, 3



  // 1-Indexed Array
  // right = 2n + 1
  // left = 2n
  // Example: 012 -- 134 -- 256 -- 378

  // n, n+1, where n increases by 2 with each index
  // left = 2n

  // right  = 2n+1

  // left = 2(0-index + 1)
  // right = 2(0-index + 1)

  // Figuring it out for yourself is good for the soul!! 

  // 2-ary: left = 2n+1, 0-indexed 
  // 3-ary: left = 3n+1, 0-indexed
  // 4-ary: left = 4n+1, 0-indexed (For example: 0, 1, 5, 21)
  // 5-ary: left = 5n+1, 0-indexed



  // Trickle down
  int curr_index = 0;
  // While children exist
  while (Heap::size() > Heap::m*curr_index + 1) 
  {
    // Print statement
    std::cout << "trickling down..." << std::endl;
    std::cout << "Current Index: " << curr_index << std::endl;
    std::cout << "Left child index: " << Heap::m * curr_index + 1 << std::endl;
    std::cout << "Heap Size: " << Heap::size() << std::endl;


  // Problem: Heap::size is always greater than 



    // TODO: Use the Comparator
    // TODO: Checks
    // Check that you're getting the correct left and right child (for 2 + 3 + 5)
    // Check that you're getting the right better
    // Check the second if (better = left child)
    // Check that the comparator works as expected
    // Check the swap

    // Print statement
    // std::cout << "trickling down" << std::endl;
    // std::cout << "current index: " << curr_index << std::endl;
    
    // Forward declaration of the better node
    T better;
    int better_index;

    // If the right child exists
    if (Heap::size() > Heap::m * curr_index + 2) {

        // Find the better of left and right
        T& left = data[Heap::m * curr_index + 1];
        T& right = data[Heap::m * curr_index + 2];

        // std::cout << "Left: " << left << std::endl;
        // std::cout << "Right: " << right << std::endl;

        if (compare(left, right)) {
            better = left;
            better_index = Heap::m * curr_index + 1;
        }

        else {
            better = right;
            better_index = Heap::m * curr_index + 2;
        }
    }
    
    // If only the left child exists
    else { 
        // Set the better as the left child
        better_index = Heap::m * curr_index + 1;
    }

    std::cout << "Better: " << data[better_index] << std::endl;

    // If the better child is better then the parent
    if (compare(data[better_index], data[curr_index])) {
        std::cout << data[curr_index] << std::endl;
        std::cout << data[better_index] << std::endl;

        std::cout << "swapping " << data[better_index] << " and " << data[curr_index] << std::endl;
        std::swap(data[curr_index], data[better_index]);

        std::cout << data[curr_index] << std::endl;
        std::cout << data[better_index] << std::endl;

        curr_index = better_index;
    }

    // If the parent is better than both children
    // else {
    break;
    // }
  }
}



#endif

