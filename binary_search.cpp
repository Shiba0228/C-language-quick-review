#include <cassert>
#include <iostream>
#include <vector>

int binarySearch(const std::vector<int>& a, int target) {
    int left = 0, right = static_cast<int>(a.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    assert(binarySearch({1, 3, 5, 7}, 5) == 2);
    assert(binarySearch({}, 5) == -1);
    std::cout << "all tests passed\n";
}
