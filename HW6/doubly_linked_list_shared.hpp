#pragma once
#include <iostream>
#include <memory>

class DoublyLinkedList {
private:
    struct Node {
        int value;
        std::shared_ptr<Node> next;
        std::shared_ptr<Node> prev;

        Node(int value) : value(value), next(nullptr), prev(nullptr) {}

        ~Node() {
            std::cout << "Destroying node " << value << "\n";
        }
    };

    std::shared_ptr<Node> head_;
    std::shared_ptr<Node> tail_;

public:
    DoublyLinkedList() = default;
    ~DoublyLinkedList() = default;

    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    void push_back(int value) {
        auto node = std::make_shared<Node>(value);
        if (!tail_) {
            head_ = tail_ = node;
        } else {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
    }

    void print_forward(std::ostream& os) const {
        auto current = head_;
        while (current) {
            os << current->value;
            if (current->next) os << " -> ";
            current = current->next;
        }
        os << "\n";
    }
};
