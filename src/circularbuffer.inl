template<typename T>
CircularBuffer<T>& CircularBuffer<T>::operator=(CircularBuffer<T>& other) {
    if (this != &other) {
        // Lock mutex during copy so the different fields are valid
        std::lock_guard<std::mutex> guard(other.mutex);

        // Create new buffer store with new capacity and copy data over
        T* new_data = new T[other.capacity];
        std::copy(other.data, other.data + other.capacity, new_data);

        // Remove old data store
        delete[] this->data;

        // Assign all fields
        this->data = new_data;
        this->capacity = other.capacity;
        this->size = other.size;
        this->start = other.start;
        this->next = other.next;
    }
    return *this;
}

template<typename T>
void CircularBuffer<T>::push(const T& element) {
    std::lock_guard<std::mutex> guard(this->mutex);

    data[this->next] = element;
    // If buffer is already full, discard last element
    if (this->size == this->capacity) {
        // Move the start index to the following element
        this->start = (this->start + 1) % this->capacity;
    } else {
        this->size++;
    }
    // Move the next index to the following element
    this->next = (this->next + 1) % this->capacity;
}

template<typename T>
T CircularBuffer<T>::pop() {
    std::lock_guard<std::mutex> guard(this->mutex);

    // Throw exception when empty
    if (this->size == 0) {
        throw std::out_of_range("No elements in buffer");
    }
    this->size--;

    // Copy start index before modifying it
    int index = this->start;
    this->start = (this->start + 1) % this->capacity;

    // Return the previously first element
    return data[index];
}

template<typename T>
int CircularBuffer<T>::count() const {
    return this->size;
}
