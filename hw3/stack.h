#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
};

template <typename T>
Stack<T>::Stack() : std::vector<T>()
{ }

template <typename T>
Stack<T>::~Stack()
{ 
    // TODO: Do we need to deallocate the vector?
}

template <typename T>
bool Stack<T>::empty() const {
    return (Stack<T>::size() == 0);
}

template <typename T>
size_t Stack<T>::size() const {
    return std::vector<T>::size();
}

template <typename T>
void Stack<T>::push(const T& item) 
{
    return std::vector<T>::push_back(item);
}

template <typename T>
void Stack<T>::pop() 
{
    if (Stack<T>::empty()) {
        throw std::underflow_error("You cannot pop an empty Stack");
    }

    // TODO: Erase first or last item in O(1)
    // Current assumption: Swap the first and the last, then erase the last
    std::swap(std::vector<T>::at(0), std::vector<T>::at(Stack<T>::size() - 1));
    std::vector<T>::pop_back();
}

template <typename T>
const T& Stack<T>::top() const
{
    if (Stack<T>::empty()) {
        throw std::underflow_error("You cannot pop an empty Stack");
    }

    return std::vector<T>::at(0);
}

#endif#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
};

template <typename T>
Stack<T>::Stack() : std::vector<T>()
{ }

template <typename T>
Stack<T>::~Stack()
{ 
    // TODO: Do we need to deallocate the vector?
}

template <typename T>
bool Stack<T>::empty() const {
    return (Stack<T>::size() == 0);
}

template <typename T>
size_t Stack<T>::size() const {
    return std::vector<T>::size();
}

template <typename T>
void Stack<T>::push(const T& item) 
{
    return std::vector<T>::push_back(item);
}

template <typename T>
void Stack<T>::pop() 
{
    if (Stack<T>::empty()) {
        throw std::underflow_error("You cannot pop an empty Stack");
    }

    // TODO: Erase first or last item in O(1)
    // Current assumption: Swap the first and the last, then erase the last
    std::swap(std::vector<T>::at(0), std::vector<T>::at(Stack<T>::size() - 1));
    std::vector<T>::pop_back();
}

template <typename T>
const T& Stack<T>::top() const
{
    if (Stack<T>::empty()) {
        throw std::underflow_error("You cannot pop an empty Stack");
    }

    return std::vector<T>::at(0);
}

#endif