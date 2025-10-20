#include<iostream>
#include <string>
#include "StackException.h"
using namespace std;

template <class T>
class StackNode {
public:
    T item;
    StackNode* next;
    StackNode(const T& e = T(), StackNode* n = NULL)
        : item(e), next(n) {}
};

template <class T>
class Stack {
public:
    Stack();
    ~Stack();
    bool isEmpty() const;
    void push(const T& newItem);
    void pop();
    void topAndPop(T& stackTop);
    void getTop(T& stackTop) const;

private:
    StackNode<T>* topPtr;
};

template <class T>
Stack<T>::Stack() : topPtr(NULL) {}

template <class T>
bool Stack<T>::isEmpty() const {
    return topPtr == NULL;
}

template <class T>
void Stack<T>::push(const T& newItem) {
    StackNode<T>* newPtr = new StackNode<T>(newItem, topPtr);
    topPtr = newPtr;
}

template <class T>
void Stack<T>::pop() {
    if (isEmpty())
        throw StackException("Stack empty");
    StackNode<T>* tmp = topPtr;
    topPtr = topPtr->next;
    delete tmp;
}

template <class T>
Stack<T>::~Stack() {
    while (!isEmpty()) pop();
}

template <class T>
void Stack<T>::getTop(T& stackTop) const {
    if (isEmpty())
        throw StackException("Stack empty");
    stackTop = topPtr->item;
}

template <class T>
void Stack<T>::topAndPop(T& stackTop) {
    getTop(stackTop);
    pop();
}

bool isBalanced(const string& str) {
    Stack<char> s;
    for (char ch : str) {
        if (ch == '{' || ch == '(' || ch == '[')
            s.push(ch);
        else if (ch == '}' || ch == ')' || ch == ']') {
            if (s.isEmpty()) return false;
            char top; s.getTop(top);
            if ((top == '(' && ch == ')') ||
                (top == '{' && ch == '}') ||
                (top == '[' && ch == ']'))
                s.pop();
            else return false;
        }
    }
    return s.isEmpty();
}

int main() {
    string expr;
    cout << "Enter a string of brackets: ";
    cin >> expr;

    if (isBalanced(expr))
        cout << "The string is balanced." << endl;
    else
        cout << "The string is NOT balanced." << endl;

    return 0;
}