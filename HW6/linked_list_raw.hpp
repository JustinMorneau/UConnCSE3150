#pragma once
#include <iostream>

class LinkedList {
private:
    struct Node {
        int value;
        Node* next;
        Node(int value) : value(value), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;

public:
    LinkedList() : head_(nullptr), tail_(nullptr) {}

    ~LinkedList() {
        Node* current = head_;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void push_back(int value) {
        Node* node = new Node(value);
        if (!tail_) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            tail_ = node;
        }
    }

    void print(std::ostream& os) const {
        Node* current = head_;
        while (current) {
            os << current->value;
            if (current->next) os << " -> ";
            current = current->next;
        }
        os << "\n";
    }
};
