#include "circularbuffer.h"

#include <chrono>
#include <thread>
#include <iostream>

void prod(CircularBuffer<long long>* buffer) {
    for (int i = 0; i < 30; i++) {
        buffer->push(2 << i);
        std::this_thread::sleep_for(std::chrono::milliseconds(i));
    }
}

void cons(CircularBuffer<long long>* buffer) {
    for (int i = 0; i < 100; i++) {
        try {
            auto element = buffer->pop();
            std::cout << "Popped " << element << std::endl;
        } catch (std::out_of_range) {}
        // Sleep longer than the first steps of the producer, some values will get replaced already
        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }
}

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
    // Use copy constructor
    CircularBuffer<int> copy = buffer;
    // Add element to the copy
    copy.push(42);

    CircularBuffer<int> copy2(2);
    // Use copy assignment
    copy2 = copy;
    // Add element to the second copy
    copy2.push(24);
    // Sizes should now all be different as a deep copy has been performed
    std::cout << "Size: " << buffer.count() << "; Copy size: " << copy.count() << "; Copy2 size: " << copy2.count() << std::endl;

    // Remove all elements from the second copy until pop throws an exception.
    while (true) {
        try {
            copy2.pop();
            std::cout << "pop" << std::endl;
        } catch (std::out_of_range) {
            break;
        }
    }
    std::cout << "end" << std::endl;

    // Real-world example with producer and consumer thread
    CircularBuffer<long long> multithread(2);
    std::thread produce(prod, &multithread);
    std::thread consume(cons, &multithread);
    produce.join();
    consume.join();
}
