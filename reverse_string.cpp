#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

void reverseString(std::string& s) {
    for (std::size_t l = 0, r = s.size(); l < r && l < --r; ++l)
        std::swap(s[l], s[r]);
}

int main() {
    std::string s = "hello";
    reverseString(s);
    assert(s == "olleh");
    std::cout << s << '\n';
}
