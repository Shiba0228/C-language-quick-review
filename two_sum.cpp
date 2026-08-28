#include <cassert>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

std::vector<int> twoSum(const std::vector<int>& a, int target) {
    std::unordered_map<long long, int> seen;
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        long long need = static_cast<long long>(target) - a[i];
        auto it = seen.find(need);
        if (it != seen.end()) return {it->second, i};
        seen[a[i]] = i;
    }
    throw std::invalid_argument("no solution");
}

int main() {
    assert((twoSum({2, 7, 11, 15}, 9) == std::vector<int>{0, 1}));
    std::cout << "all tests passed\n";
}
