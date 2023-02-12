#include "circularbuffer.h"

#include <iostream>

int main() {
    CircularBuffer<int> buffer(3);
    buffer.push(7);
    buffer.push(3);
    buffer.push(25);
    buffer.push(1);
    buffer.push(2);
    buffer.push(3);
    std::cout << "Size: " << buffer.count() << std::endl;

    int element = buffer.pop();
    buffer.push(4);
    std::cout << element << ", " << buffer.pop() << ", " << buffer.pop() << ", " << buffer.pop() << std::endl;
    std::cout << "Size: " << buffer.count() << std::endl;
    CircularBuffer<int> copy = buffer;
    copy.push(42);

    CircularBuffer<int> copy2(2);
    copy2 = copy;
    copy2.push(24);
    std::cout << "Size: " << buffer.count() << "; Copy size: " << copy.count() << "; Copy2 size: " << copy2.count() << std::endl;

    while (true) {
        try {
            copy2.pop();
            std::cout << "pop" << std::endl;
        } catch (std::out_of_range) {
            break;
        }
    }
    std::cout << "end" << std::endl;
}
