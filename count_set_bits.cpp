#include <cassert>
#include <cstdint>
#include <iostream>

unsigned countSetBits(std::uint32_t value) {
    unsigned count = 0;
    while (value) {
        value &= value - 1U;
        ++count;
    }
    return count;
}

int main() {
    assert(countSetBits(0U) == 0 && countSetBits(0b101101U) == 4);
    std::cout << "all tests passed\n";
}
