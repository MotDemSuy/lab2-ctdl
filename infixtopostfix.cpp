#include <iostream>
#include <stack>
#include <string>
using namespace std;

int getPrecedence(char op) {
	if (op == '^') {
		return 3;
	}
	if (op == '*' || op == '/') {
		return 2;
	}
	if (op == '+' || op == '-') {
		return 1;
	}
	return -1;
}

// Function to check if operator is right-associative
bool isRightAssociative(char c) {
	return c == '^';
}

string infixToPostfix(string& s) {
	stack<char> st;
	string res;

	for (int i = 0; i < s.length(); i++) {
		char c = s[i];

		// If operand, add to result
		if ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9'))
			res += c;

		// If '(', push to stack
		else if (c == '(')
			st.push('(');

		// If ')', pop until '('
		else if (c == ')') {
			while (!st.empty() && st.top() != '(') {
				res += st.top();
				st.pop();
			}
			st.pop();
		}

		// If operator
		else {
			while (!st.empty() && st.top() != '(' &&
				(getPrecedence(st.top()) > getPrecedence(c) ||
					(getPrecedence(st.top()) == getPrecedence(c) && !isRightAssociative(c)))) {
				res += st.top();
				st.pop();
			}
			st.push(c);
		}
	}

	// Pop remaining operators
	while (!st.empty()) {
		res += st.top();
		st.pop();
	}

	return res;
}

int main() {
	string exp = "a*(b+c)/d"
	cout << infixToPostfix(exp);
	return 0;
}
