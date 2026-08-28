#include <cassert>
#include <iostream>

struct Node { int value; Node* next; };

bool hasCycle(const Node* head) {
    const Node* slow = head;
    const Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

int main() {
    Node c{3, nullptr}, b{2, &c}, a{1, &b};
    assert(!hasCycle(&a));
    c.next = &b;
    assert(hasCycle(&a));
    std::cout << "all tests passed\n";
}
