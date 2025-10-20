#include<iostream>
#include<string>
using namespace std;

class StackException {
public:
    StackException(const string& err) : error(err) {}
    string error;
};