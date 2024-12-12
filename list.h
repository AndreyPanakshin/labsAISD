#pragma once
#include <iostream>
#include <stdexcept>
#include <random>
#include <unordered_set>

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;

    void copy_list(const LinkedList& other) {
        Node<T>* current = other.head;
        while (current) {
            push_tail(current->data);
            current = current->next;
        }
    }

    void clear_list() {
        while (head) {
            pop_head();
        }
    }

public:

    LinkedList() : head(nullptr), tail(nullptr), size(0) {}


    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        copy_list(other);
    }


    LinkedList(size_t n, T min_val, T max_val) : head(nullptr), tail(nullptr), size(0) {
        std::mt19937 gen(42);
        std::uniform_int_distribution<T> dist(min_val, max_val);

        for (size_t i = 0; i < n; ++i) {
            push_tail(dist(gen));
        }
    }


    ~LinkedList() {
        clear_list();
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear_list();
            copy_list(other);
        }
        return *this;
    }


    void push_tail(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (!tail) {
            head = tail = new_node;
            head->next = tail;
            head->prev = tail;
            tail->next = head;
            tail->prev = head;
        }
        else {
            new_node->prev = tail;
            new_node->next = head;
            tail->next = new_node;
            head->prev = new_node;
            tail = new_node;
        }
        ++size;
    }


    void push_head(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (!head) {
            head = tail = new_node;
            head->next = tail;
            head->prev = tail;
            tail->next = head;
            tail->prev = head;
        }
        else {
            new_node->next = head;
            new_node->prev = tail;
            head->prev = new_node;
            tail->next = new_node;
            head = new_node;
        }
        ++size;
    }
    void push_tail(LinkedList& other) {
        if (other.size == 0) {
            return;
        }

        if (size == 0) {
            head = other.head;
            tail = other.tail;
        }
        else {

            Node<T>* current = other.tail;
            current->next = head;
            head->prev = current;
            tail->next = other.head;
            other.head->prev = tail;
            tail = other.tail;
        }
        size += other.size;
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
  
   
 
    void push_head(LinkedList& other) {
        if (other.size == 0) {
            return;
        }
        if (size == 0) {
            head = other.head;
        }
        else {
            Node<T>* tail = head->prev;
            Node<T>* other_tail = other.head->prev;
            other_tail->next = head;
            head->prev = other_tail;
            other.head->prev = tail;
            tail->next = other.head;
            head = other.head;
        }
        size += other.size;
        other.head = nullptr;
        other.size = 0;
    }

    void pop_head() {
        if (!head) throw std::underflow_error("List is empty.");
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node<T>* temp = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete temp;
        }
        --size;
    }


    void pop_tail() {
        if (!tail) throw std::underflow_error("List is empty.");
        if (head == tail) {
            delete tail;
            head = tail = nullptr;
        }
        else {
            Node<T>* temp = tail;
            tail = tail->prev;
            head->prev = tail;
            tail->next = head;
            delete temp;
        }
        --size;
    }


    void delete_node(T value) {
        if (size == 0) return; 
        Node<T>* current = head;
        Node<T>* end = head; 
        do {
            if (current->data == value) {
                if (current == head) {
                    pop_head();
                    current = head;
                }
                else if (current == tail) {
                    pop_tail();
                    current = head; 
                }
                else {
                    
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    Node<T>* to_delete = current; 
                    current = current->next; 
                    delete to_delete;
                    --size;
                }
            }
            else {
                current = current->next; 
            }
        } while (current != end);
    }



    T operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range.");
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    
    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range.");
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    size_t get_size() const {
        return size;
    }


    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
        Node<T>* current = list.head;
        if (current) {
            do {
                os << current->data << " ";
                current = current->next;
            } while (current != list.head);
        }
        return os;
    }
};

