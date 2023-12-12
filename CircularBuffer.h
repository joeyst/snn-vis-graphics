
#ifndef _CIRCULAR_BUFFER_H
#define _CIRCULAR_BUFFER_H

// SOURCE: ChatGPT. 
#include <vector>

template <typename T>
class CircularBuffer {
public:
    CircularBuffer(std::size_t size) : buffer(size), currentIndex(0) {}

    // Function to add an element to the buffer
    void Push(const T& item) {
        currentIndex = (currentIndex + 1) % buffer.size();
        buffer[currentIndex] = item;
    }

    // Function to access elements
    T& operator[](std::size_t index) {
        return buffer[(currentIndex + index) % buffer.size()];
    }

    // Function to get current element. 
    T Peek() {
        return buffer[currentIndex];
    }

    // Function to get the vector. 
    std::vector<T> GetVector() {
        return buffer;
    }

private:
    std::vector<T> buffer;
    std::size_t currentIndex;
};

#endif
