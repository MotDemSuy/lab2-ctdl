#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

template <class T>
class Stack {
public:
    Stack(int n) {
        maxSize = n;
        items = new T[maxSize];
        top = -1;
    }
    ~Stack() { delete[] items; }

    bool isEmpty() const { return top < 0; }
    bool isFull() const { return top >= maxSize - 1; }

    void push(const T& x) {
        if (!isFull()) items[++top] = x;
    }

    bool topAndPop(T& x) {
        if (isEmpty()) return false;
        x = items[top--];
        return true;
    }

private:
    T* items;
    int top;
    int maxSize;
};

int evaluatePrefix(string expr, int n) {
    Stack<int> st(n);
    string token;
    stringstream ss(expr);

    string* tokens = new string[n];
    int count = 0;
    while (ss >> token && count < n)
        tokens[count++] = token;

    cout << "\nQUY TRINH TINH PREFIX" << endl;

    for (int i = count - 1; i >= 0; i--) {
        string t = tokens[i];
        if (isdigit(t[0]) || (t[0] == '-' && t.size() > 1 && isdigit(t[1]))) {
            st.push(stoi(t));
            cout << "Day so " << t << " vao stack" << endl;
        } else {
            int a, b;
            if (!st.topAndPop(a) || !st.topAndPop(b)) {
                cout << "Stack thieu so!" << endl;
                delete[] tokens;
                return 0;
            }

            int result = 0;
            if (t == "+") result = a + b;
            else if (t == "-") result = a - b;
            else if (t == "*") result = a * b;
            else if (t == "/") result = a / b;
            else {
                cout << "Phep toan khong hop le!" << endl;
                delete[] tokens;
                return 0;
            }

            cout << "Thuc hien: " << a << " " << t << " " << b << " = " << result << endl;
            st.push(result);
        }
    }

    int finalResult;
    st.topAndPop(finalResult);
    delete[] tokens;
    return finalResult;
}

int main() {
    string expr;
    int n;

    cout << "nhap kich thuoc toi da cua stack: ";
    cin >> n;
    cin.ignore();

    cout << "nhap bieu thuc prefix: ";
    getline(cin, expr);

    int result = evaluatePrefix(expr, n);
    cout << "\nket qua: " << result << endl;

    return 0;
}
