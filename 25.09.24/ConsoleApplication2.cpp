#include <iostream>
#include <memory>
#include <stdexcept>  

template <typename T>
class ArrayList {
public:
    ArrayList() : size_(0), capacity(2), data(new T[capacity]) {}

    void push_back(const T& value) {
        if (size_ == capacity) {
            capacity *= 2;
            T* new_data = new T[capacity];
            for (int i = 0; i < size_; i++) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
        }
        data[size_++] = value;
    }

    T at(int index) const {
        if (index < 0 || index >= size_) {
            throw std::runtime_error("Index out of bounds");
        }
        return data[index];
    }

    int size() const {
        return size_;
    }

private:
    int size_;
    int capacity;
    T* data;
};


// Пример использования ArrayList и Queue
int main() {
    ArrayList<int> array_list;
    array_list.push_back(1);
    array_list.push_back(2);
    array_list.push_back(3);

    std::cout << "ArrayList size: " << array_list.size() << std::endl;
    std::cout << "ArrayList at(0): " << array_list.at(0) << std::endl;
    std::cout << "ArrayList at(1): " << array_list.at(1) << std::endl;
    std::cout << "ArrayList at(2): " << array_list.at(2) << std::endl;
}
