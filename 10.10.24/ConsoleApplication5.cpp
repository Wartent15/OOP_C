#include <iostream>
#include <vector>
#include <bitset>

class Bitset {
private:
    std::vector<bool> bits;  
    size_t size;             

public:
    explicit Bitset(size_t n) : size(n), bits(n, false) {}

    size_t getSize() const {
        return size;
    }

    bool get(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return bits[index];
    }

    void set(size_t index, bool value) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        bits[index] = value;
    }

    void flip() {
        for (size_t i = 0; i < size; ++i) {
            bits[i] = !bits[i];
        }
    }

    Bitset operator&(const Bitset& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Bitsets must have the same size");
        }
        Bitset result(size);
        for (size_t i = 0; i < size; ++i) {
            result.set(i, bits[i] && other.bits[i]);
        }
        return result;
    }

    Bitset operator|(const Bitset& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Bitsets must have the same size");
        }
        Bitset result(size);
        for (size_t i = 0; i < size; ++i) {
            result.set(i, bits[i] || other.bits[i]);
        }
        return result;
    }

    Bitset operator^(const Bitset& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Bitsets must have the same size");
        }
        Bitset result(size);
        for (size_t i = 0; i < size; ++i) {
            result.set(i, bits[i] != other.bits[i]);
        }
        return result;
    }

    Bitset operator<<(size_t shift) const {
        if (shift >= size) {
            throw std::out_of_range("Shift out of range");
        }
        Bitset result(size);
        for (size_t i = 0; i < size - shift; ++i) {
            result.set(i, bits[i + shift]);
        }
        return result;
    }

    Bitset operator>>(size_t shift) const {
        if (shift >= size) {
            throw std::out_of_range("Shift out of range");
        }
        Bitset result(size);
        for (size_t i = shift; i < size; ++i) {
            result.set(i, bits[i - shift]);
        }
        return result;
    }

    Bitset rotateLeft(size_t shift) const {
        if (shift >= size) {
            shift %= size;  
        }
        Bitset result(size);
        for (size_t i = 0; i < size; ++i) {
            result.set(i, bits[(i + shift) % size]);
        }
        return result;
    }

    Bitset rotateRight(size_t shift) const {
        if (shift >= size) {
            shift %= size;  
        }
        Bitset result(size);
        for (size_t i = 0; i < size; ++i) {
            result.set(i, bits[(i + size - shift) % size]);
        }
        return result;
    }

    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << bits[i];
        }
        std::cout << std::endl;
    }
};

int main() {
    try {
        Bitset b1(8);
        b1.set(0, true);
        b1.set(3, true);
        b1.set(5, true);
        std::cout << "b1: ";
        b1.print();

        Bitset b2(8);
        b2.set(1, true);
        b2.set(3, true);
        b2.set(6, true);
        std::cout << "b2: ";
        b2.print();

        Bitset b3 = b1 & b2;
        std::cout << "b1 & b2: ";
        b3.print();

        Bitset b4 = b1 | b2;
        std::cout << "b1 | b2: ";
        b4.print();

        Bitset b5 = b1 ^ b2;
        std::cout << "b1 ^ b2: ";
        b5.print();

        Bitset b6 = b1 << 2;
        std::cout << "b1 << 2: ";
        b6.print();

        Bitset b7 = b1 >> 2;
        std::cout << "b1 >> 2: ";
        b7.print();

        Bitset b8 = b1.rotateLeft(3);
        std::cout << "b1 rotateLeft(3): ";
        b8.print();

        Bitset b9 = b1.rotateRight(3);
        std::cout << "b1 rotateRight(3): ";
        b9.print();

        b1.flip();
        std::cout << "b1 flipped: ";
        b1.print();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
