#include <iostream>


template <typename T>
class Node {
public:
    T data;
    std::shared_ptr<Node<T>> next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    size_t list_size;

public:
    LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

    void push_front(const T& value) {
        auto new_node = std::make_shared<Node<T>>(value);
        if (is_empty()) {
            tail = new_node;
        }
        new_node->next = head;
        head = new_node;
        ++list_size;
    }

    void push_back(const T& value) {
        auto new_node = std::make_shared<Node<T>>(value);
        if (is_empty()) {
            head = new_node;
        }
        else {
            tail->next = new_node;
        }
        tail = new_node;
        ++list_size;
    }

    void pop_front() {
        if (is_empty()) {
            std::cout << "Список пуст, удаление невозможно." << std::endl;
            return;
        }
        head = head->next;
        --list_size;
        if (is_empty()) {
            tail = nullptr; 
        }
    }

    void pop_back() {
        if (is_empty()) {
            std::cout << "Список пуст, удаление невозможно." << std::endl;
            return;
        }

        if (head == tail) { 
            head = nullptr;
            tail = nullptr;
        }
        else {
            auto current = head;
            while (current->next != tail) {
                current = current->next;
            }
            current->next = nullptr;
            tail = current;
        }
        --list_size;
    }

    std::shared_ptr<Node<T>> find(const T& value) {
        auto current = head;
        while (current) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void remove(const T& value) {
        if (is_empty()) {
            std::cout << "Список пуст, удаление невозможно." << std::endl;
            return;
        }

        if (head->data == value) {
            pop_front();
            return;
        }

        auto current = head;
        while (current->next) {
            if (current->next->data == value) {
                current->next = current->next->next;
                if (current->next == nullptr) { 
                    tail = current;
                }
                --list_size;
                return;
            }
            current = current->next;
        }
        std::cout << "Элемент " << value << " не найден." << std::endl;
    }

    void print() const {
        auto current = head;
        if (is_empty()) {
            std::cout << "Список пуст." << std::endl;
            return;
        }
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    bool is_empty() const {
        return list_size == 0;
    }

    size_t size() const {
        return list_size;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    LinkedList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    list.print(); 

    list.pop_front();
    list.print(); 

    list.pop_back();
    list.print(); 

    list.remove(10);
    list.print(); 

    for (int i = 1; i <= 5; ++i) {
        list.push_back(i);
    }
    list.print(); 

    auto found = list.find(3);
    if (found) {
        std::cout << "Элемент найден: " << found->data << std::endl;
    }
    else {
        std::cout << "Элемент не найден." << std::endl;
    }

    std::cout << "Размер списка: " << list.size() << std::endl; 
    std::cout << "Список пуст: " << list.is_empty() << std::endl; 

}