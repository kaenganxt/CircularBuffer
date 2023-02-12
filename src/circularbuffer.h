#include <stdexcept>
#include <mutex>

/**
 * A thread-safe, generic, fixed-size circular buffer implementation.
 * 
 * Elements can be added suing the `push` method and removed using `pop`.
 * When the buffer is full, a new element discards the first element.
 */
template<typename T>
class CircularBuffer {

private:
    T* data;
    unsigned int capacity, size, start, next;
    std::mutex mutex;

public:
    /**
     * Construct a new empty buffer with the given capacity.
     */
    CircularBuffer(unsigned int capacity) : data(new T[capacity]), capacity(capacity), start(0), next(0), size(0) {
    }

    /**
     * Copy constructor to perform a deep copy of the buffer.
     */
    CircularBuffer(const CircularBuffer<T>& copy) : size(copy.size), capacity(copy.capacity), start(copy.start), next(copy.next), data(new T[copy.capacity]) {
        std::copy(copy.data, copy.data + copy.capacity, data);
    }

    /**
     * Destructor.
     */
    ~CircularBuffer() {
        delete[] data;
    }

    /**
     * Assignment operator to perform a deep copy of the buffer.
     */
    CircularBuffer<T>& operator=(CircularBuffer<T>& other);

    /**
     * Add a new element to the end of the buffer.
     * 
     * The element is copied before being added.
     * If the buffer is full, the given element is added and the oldest element is discarded.
     * This method is thread-safe.
     */
    void push(const T& element);

    /**
     * Remove and return the element at the beginning of the buffer.
     * 
     * If the buffer is empty, an `std::out_of_range` exception is thrown.
     * To check the size exception-free, use the `count` method.
     * This method is thread-safe.
     */
    T pop();

    /**
     * Returns the number of elements contained in the buffer.
     */
    int count() const;
};

#include "circularbuffer.inl"
