#include <cassert>
#include <iostream>
#include <list>
#include <optional>
#include <unordered_map>

class LruCache {
    using Item = std::pair<int, int>;
    using It = std::list<Item>::iterator;
    std::size_t capacity_;
    std::list<Item> items_;
    std::unordered_map<int, It> map_;
public:
    explicit LruCache(std::size_t capacity) : capacity_(capacity) {}
    std::optional<int> get(int key) {
        auto it = map_.find(key);
        if (it == map_.end()) return std::nullopt;
        items_.splice(items_.begin(), items_, it->second);
        return it->second->second;
    }
    void put(int key, int value) {
        if (!capacity_) return;
        auto it = map_.find(key);
        if (it != map_.end()) {
            it->second->second = value;
            items_.splice(items_.begin(), items_, it->second);
            return;
        }
        items_.emplace_front(key, value); map_[key] = items_.begin();
        if (items_.size() > capacity_) {
            map_.erase(items_.back().first); items_.pop_back();
        }
    }
};

int main() {
    LruCache c(2); c.put(1, 10); c.put(2, 20); c.get(1); c.put(3, 30);
    assert(!c.get(2) && c.get(1) == 10 && c.get(3) == 30);
    std::cout << "all tests passed\n";
}
