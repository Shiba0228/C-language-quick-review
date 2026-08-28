#include <cassert>
#include <iostream>
#include <stack>
#include <string>

bool validBrackets(const std::string& s) {
    std::stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') st.push(c);
        else {
            if (st.empty()) return false;
            char open = st.top(); st.pop();
            if (!((open == '(' && c == ')') || (open == '[' && c == ']') ||
                  (open == '{' && c == '}'))) return false;
        }
    }
    return st.empty();
}

int main() {
    assert(validBrackets("{[()]}") && !validBrackets("([)]"));
    std::cout << "all tests passed\n";
}
