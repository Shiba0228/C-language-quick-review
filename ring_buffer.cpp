#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <optional>

template<std::size_t N> class RingBuffer {
    static_assert(N > 0);
    std::array<std::uint8_t, N> data_{};
    std::size_t head_ = 0, tail_ = 0, size_ = 0;
public:
    bool push(std::uint8_t value) {
        if (size_ == N) return false;
        data_[head_] = value; head_ = (head_ + 1) % N; ++size_; return true;
    }
    std::optional<std::uint8_t> pop() {
        if (!size_) return std::nullopt;
        auto value = data_[tail_]; tail_ = (tail_ + 1) % N; --size_; return value;
    }
};

int main() {
    RingBuffer<2> b;
    assert(b.push(1) && b.push(2) && !b.push(3));
    assert(b.pop() == 1 && b.pop() == 2 && !b.pop());
    std::cout << "all tests passed\n";
}
