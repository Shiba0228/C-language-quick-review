#include <cassert>
#include <iostream>

struct Node { int value; Node* next; };

Node* reverseList(Node* head) {
    Node* previous = nullptr;
    while (head) {
        Node* next = head->next;
        head->next = previous;
        previous = head;
        head = next;
    }
    return previous;
}

int main() {
    Node c{3, nullptr}, b{2, &c}, a{1, &b};
    Node* head = reverseList(&a);
    assert(head == &c && c.next == &b && b.next == &a && !a.next);
    std::cout << "all tests passed\n";
}
